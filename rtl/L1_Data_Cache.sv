// Write HIT:  Write-back: In a write-back cache, data is written to the cache and only later to the main memory when the cache line is replaced. 
// Write MISS: Write allocate: when a write miss occurs, the cache line is loaded into the cache, and then the write operation is performed.
// Look-through:  which means it checks the main memory for cache misses.
// LRU (Least Recently Used):  which means the least recently used cache line is selected for replacement.
// small caches are low prone to the a very low temporal double-bit error rate.

// 2 words per block., Non blocking cache to implement
// to make synthesis easy we need to write the memory in SRAM style

module sram_module(
    input clk,
    input write_enable, read_enable,
    input [8:0] set_index, 
    input way_select, 
    input [1:0] data_mode,
    input [31:0] write_data, 
    output logic [31:0] read_data  
);
    // Constants for cache configuration
    localparam BLOCK_SIZE    = 4;         // 4 bytes since our words are 32-bit
    localparam CACHE_SIZE    = 4 * 1024;  // 4 KB
    localparam ASSOCIATIVITY = 2;     
    
    localparam BLOCK_WIDTH   = BLOCK_SIZE * 8; //32 bits
    localparam NUM_SETS      = CACHE_SIZE/(BLOCK_SIZE * ASSOCIATIVITY); //512 sets
    localparam ADDR_WIDTH    = 32; 

    reg [BLOCK_WIDTH -1:0] memory_array [0:NUM_SETS * ASSOCIATIVITY - 1];
    wire [ADDR_WIDTH -1:0] actual_address = set_index * ASSOCIATIVITY + way_select;   
//    wire gated_clk = clk & (write_enable | read_enable); //Power saving Consideration
//  but the write or read is continously high for this module
    
    always @(posedge clk) begin
        if (write_enable) begin
            if (actual_address < (NUM_SETS * ASSOCIATIVITY)) begin

                //Enables updating of only least significant byte, least signficant half, or entire word
                case(data_mode)
                0: memory_array[actual_address] <= {memory_array[actual_address][31:8], write_data[7:0]};
                1: memory_array[actual_address] <= {memory_array[actual_address][31:15], write_data[15:0]};
                default: memory_array[actual_address] <= write_data;
                endcase

            end
                
        end else if(read_enable)begin
            if (actual_address < (NUM_SETS * ASSOCIATIVITY))
                read_data = memory_array[actual_address];
        end
        // Handle out of bounds.
    end 
endmodule : sram_module

module L1_Data_Cache(
    input clk,
    input rstn,
    input write_enable, read_enable,
    input [31:0] request_address,
    input [31:0] write_data,
    input [1:0] data_mode,
    output logic [31:0] response_data,
    output logic [1:0] c_state,
    
    // To LOWER MEMORY
    output logic mem_request,
    output logic mem_write_enable,
    output logic [31:0] mem_address, 
    output logic [31:0] mem_write_data,
    input [31:0] mem_response_data,
    input mem_ready
);
    // Hardcoded parameters for the data cache
    localparam CACHE_SIZE    = 4 * 1024;   // Cache size: 4 KB
    localparam BLOCK_SIZE    = 4;          // Block size: 4 bytes (32 bits)
    localparam ASSOCIATIVITY = 2;          // 2-way
    localparam DATA_WIDTH    = 32;
    
    localparam BLOCK_WIDTH   = BLOCK_SIZE * 8; //32 bits
    localparam NUM_SETS      = CACHE_SIZE/(BLOCK_SIZE * ASSOCIATIVITY); // 512 sets
    localparam ADDR_WIDTH    = 32;                        

    // Calculating the number of bits for offset, index, and tag
    localparam OFFSET_WIDTH   = $clog2(BLOCK_SIZE);    // 2 bits
    localparam INDEX_WIDTH    = $clog2(NUM_SETS);       // 9 bits
    localparam TAG_WIDTH      = ADDR_WIDTH - OFFSET_WIDTH - INDEX_WIDTH;  // 21 bits
  
    // Internal Variables
    
    //reg [BLOCK_WIDTH- 1:0] cache_data [0:NUM_SETS-1][0:ASSOCIATIVITY-1];
    //need to add offset access
    
    reg [TAG_WIDTH - 1:0] cache_tags [0:NUM_SETS-1][0:ASSOCIATIVITY-1];
    reg valid [0:NUM_SETS-1][0:ASSOCIATIVITY-1];
    reg dirty [0:NUM_SETS-1][0:ASSOCIATIVITY-1];
    reg [ASSOCIATIVITY-1:0] lru_counter [0:NUM_SETS-1];
    
    reg hit;
    reg [ASSOCIATIVITY-1:0] way, lru_way;
    
    reg sram_read_req =0;

    typedef enum integer {IDLE, CHECK_TAG, WRITEBACK, FILL} cache_state_t;
    cache_state_t state = IDLE;

    typedef struct packed{
        logic [31:0] address;
        logic [TAG_WIDTH-1:0] tag;
        logic [INDEX_WIDTH-1:0] index;
        logic [OFFSET_WIDTH-1:0] offset;
    }current_address_t;
    current_address_t current_addr;
    
    reg [31:0] sram_read_data;
    typedef struct packed{
        logic [31:0] write_data;
        logic write_enable;
        logic read_enable;
        logic way;
        logic [1:0] data_mode,
        logic [8:0] index;

    }sram_data_t;
 
    sram_module cache_data_sram (
        .clk(clk),
        .write_enable   (put_sram_data.write_enable),
        .read_enable    (put_sram_data.read_enable),
        .set_index      (put_sram_data.index),
        .way_select     (put_sram_data.way),
        .write_data     (put_sram_data.write_data),
        .data_mode      (put_sram_data.data_mode),
        .read_data      (sram_read_data)
    );
     
    // LRU Function
    function integer get_lru_way(input integer set_index);
        integer i;
        reg [ASSOCIATIVITY-1:0] max_count;
        begin
            max_count = 0;
            //max_count = -1; -1 here is 32'hFFFFFFFF turnication happens and max_count will be 3
            lru_way = 0;
            for (i = 0; i < ASSOCIATIVITY; i = i + 1) begin            
                if (lru_counter[set_index][i] > max_count) begin
                    max_count = lru_counter[set_index][i];
                    lru_way = i;
                end
            end
            get_lru_way = lru_way;
        end
    endfunction
    
    // === === ===   Helper Tasks   === === ===
    task handle_cache_hit;
        begin
            if (write_enable) begin               
                set_sram_write_request(current_addr.index, way, write_data, data_mode);                              
                dirty[current_addr.index][way] <= 1;
                state <= IDLE;
            end else if (read_enable) begin
                if(!sram_read_req) begin 
                set_sram_read_request(current_addr.index, way);
                sram_read_req <= 1;
                end else begin 
                response_data <= sram_read_data;
                sram_read_req <=0;
                state <= IDLE;
                end
            end
            update_lru_counters(current_addr.index, way);
        end
    endtask

    task handle_cache_miss;
        begin
            if (dirty[current_addr.index][lru_way]) begin
                state <= WRITEBACK;
            end else begin
                state <= FILL;
            end
        end
    endtask
    
    task set_sram_read_request;
        input integer index, way;
        begin
            put_sram_data.read_enable <= 1;
            put_sram_data.write_enable <= 0;
            put_sram_data.index <= index;
            put_sram_data.way <= way;
        end
    endtask
    
    task set_sram_write_request;
        input integer index, way, data, data_mode;
        begin
            put_sram_data.write_enable <= 1;
            put_sram_data.read_enable <= 0;
            put_sram_data.index <= index;
            put_sram_data.way <= way;
            put_sram_data.write_data <= data;
            put_sram_data.data_mode <= data_mode;
        end
    endtask
    
    task set_mem_request;
        input [31:0] address, data;
        input write_enable;
        begin
            mem_address <= address;
            mem_write_enable <= write_enable;
            mem_request <= 1;
            mem_write_data <= data;
        end
    endtask
    
    task update_lru_counters(input integer set_index, input integer accessed_way);
        integer i;
        begin
            for (i = 0; i < ASSOCIATIVITY; i = i + 1) begin
                if (i == accessed_way) begin
                    lru_counter[set_index][i] <= 0;
                end else if (lru_counter[set_index][i] != (ASSOCIATIVITY - 1)) begin
                    lru_counter[set_index][i] <= lru_counter[set_index][i] + 1;
                end
            end
        end
    endtask
    
    //=== === ===   Cache Operation Tasks   === === ===
    task reset_cache;
        integer i, j;
        begin
            // resetting all these in single clock?
            // use valid bits to reset may be
            state <= IDLE;
            for (i = 0; i < NUM_SETS; i = i+1) begin
                for (j = 0; j < ASSOCIATIVITY; j = j+1) begin
                    
                    set_sram_write_request(i, j, 0);
                    cache_tags[i][j] <= 0;
                    valid[i][j] <= 0;
                    dirty[i][j] <= 0;
//                    lru_counter[i][j] <= j; // biased
                    lru_counter[i][j] <= 1; // still no
                end
            end
        end
    endtask

    task idle_state_logic;
        begin
            if (write_enable || read_enable) begin
                current_addr.address <= request_address;
                current_addr.tag     <= request_address[ADDR_WIDTH-1 -: TAG_WIDTH];
                current_addr.index   <= request_address[(ADDR_WIDTH - TAG_WIDTH - 1)-: INDEX_WIDTH];
                current_addr.offset  <= request_address[OFFSET_WIDTH-1 -: OFFSET_WIDTH];                      
                state <= CHECK_TAG;
            end
        end
    endtask

    task check_tag_logic;
        integer i;
        begin
            hit = 0;
            // have to parallel check for better performance and parallely start the sram
            // instantiate the sram in prev state maybe
            lru_way = get_lru_way(current_addr.index); 
            for (i = 0; i < ASSOCIATIVITY; i = i + 1) begin
                if (valid[current_addr.index][i] && cache_tags[current_addr.index][i] == current_addr.tag) begin
                    hit = 1;
                    way = i;                
                    break;
                end
            end
            if (hit) begin
                handle_cache_hit();
            end else begin
                handle_cache_miss();
            end
        end
    endtask
 
    task writeback_logic;
        reg [31:0] writeback_address;
        begin
            writeback_address = {cache_tags[current_addr.index][lru_way], current_addr.index, {OFFSET_WIDTH{1'b0}}};
            if (!sram_read_req) begin
                set_sram_read_request(current_addr.index, lru_way);
                sram_read_req <= 1;
            end else begin 
                set_mem_request(writeback_address, sram_read_data, 1);
                if (mem_ready) begin
                    mem_write_enable <= 0;
                    mem_request <= 0;
                    sram_read_req <= 0;
                    state <= FILL; 
                end 
            end
        end
    endtask
    
    task fill_logic;
        begin  
            if (!mem_request) begin
                set_mem_request(current_addr.address, 0, 0);
            end else if (mem_ready) begin
                set_sram_write_request(current_addr.index, lru_way, mem_response_data);
                cache_tags[current_addr.index][lru_way] <= current_addr.tag;
                valid[current_addr.index][lru_way] <= 1;
                dirty[current_addr.index][lru_way] <= 0; 
                update_lru_counters(current_addr.index, lru_way);
                mem_request <= 0; 
                state <= CHECK_TAG; 
            end
        end
    endtask

    // Main Cache Operation 
    always @(posedge clk, negedge rstn) begin
        if (rstn == 0) begin
            reset_cache();
        end else begin
            case (state)
                IDLE: begin
                    idle_state_logic();
                    c_state <= 0;
                end
                CHECK_TAG: begin
                    check_tag_logic();
                    c_state <= 1; 
                end
                WRITEBACK: begin
                    writeback_logic();
                    c_state <= 2; 
                end
                FILL: begin
                    fill_logic();
                    c_state <= 3; 
                end
                default: begin
                    idle_state_logic();
                    c_state <= 0; 
                end
            endcase
        end
    end   
endmodule