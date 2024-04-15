module sram_module(
    input clk,
    input write_enable, read_enable,
    input [8:0] set_index, 
    input way_select, 
    input [31:0] write_data, 
    output logic [31:0] read_data  
);
    // Constants for cache configuration
    localparam BLOCK_SIZE    = 4;         // 4 bytes since our Ins are 32-bit
    localparam CACHE_SIZE    = 4 * 256;  // 1 KB
    localparam ASSOCIATIVITY = 2;     
    
    localparam BLOCK_WIDTH   = BLOCK_SIZE * 8; //32 bits
    localparam NUM_SETS      = CACHE_SIZE/(BLOCK_SIZE * ASSOCIATIVITY); //128 sets
    localparam ADDR_WIDTH    = 32; 

    reg [BLOCK_WIDTH -1:0] memory_array [0:NUM_SETS * ASSOCIATIVITY - 1];
    wire [ADDR_WIDTH -1:0] actual_address = set_index * ASSOCIATIVITY + way_select;   


    always @(posedge clk) begin
        if (write_enable) begin

            if (actual_address < (NUM_SETS * ASSOCIATIVITY)) 
            begin
                memory_array[actual_address] <= write_data;
            end
                
        end else if(read_enable)begin
            if (actual_address < (NUM_SETS * ASSOCIATIVITY))
                read_data = memory_array[actual_address];
        end
        
    end 
endmodule : sram_module

module L1_Data_Cache(
    input clk,
    input rstn,
    input write_enable, read_enable,
    input [31:0] request_address,
    input [31:0] write_data,
    output logic [31:0] response_data,
    output logic [1:0] c_state,
    
    // To LOWER MEMORY
    output logic mem_request,
    output logic [31:0] mem_address, 
    output logic mem_write_enable,
    input [31:0] mem_response_data,
    input mem_ready
);
    // Hardcoded parameters for the data cache
    localparam CACHE_SIZE    = 4 * 256;   // Cache size: 1 KB
    localparam BLOCK_SIZE    = 4;          // Block size: 4 bytes (32 bits)
    localparam ASSOCIATIVITY = 2;          // 2-way
    localparam DATA_WIDTH    = 32;
    
    localparam BLOCK_WIDTH   = BLOCK_SIZE * 8; //32 bits
    localparam NUM_SETS      = CACHE_SIZE/(BLOCK_SIZE * ASSOCIATIVITY); // 128 sets
    localparam ADDR_WIDTH    = 32;                        

    // Calculating the number of bits for index, and tag
    localparam INDEX_WIDTH    = $clog2(NUM_SETS);       // 7 bits
    localparam TAG_WIDTH      = ADDR_WIDTH - INDEX_WIDTH;  // 25 bits
  
    // Internal Variables
    
    reg [TAG_WIDTH - 1:0] cache_tags [0:NUM_SETS-1][0:ASSOCIATIVITY-1];
    reg valid [0:NUM_SETS-1][0:ASSOCIATIVITY-1];
    reg [ASSOCIATIVITY-1:0] lru_counter [0:NUM_SETS-1];
    
    reg hit;
    reg [ASSOCIATIVITY-1:0] way, lru_way;
    
    reg sram_read_req =0;

    typedef enum integer {IDLE, CHECK_TAG, FILL} cache_state_t;
    cache_state_t state = IDLE;

    typedef struct packed{
        logic [31:0] address;
        logic [TAG_WIDTH-1:0] tag;
        logic [INDEX_WIDTH-1:0] index;
    }current_address_t;
    current_address_t current_addr;
    
    reg [31:0] sram_read_data;
    typedef struct packed{
        logic [31:0] write_data;
        logic write_enable;
        logic read_enable;
        logic way;
        logic [8:0] index;

    }sram_data_t;

    sram_data_t put_sram_data;
 
    sram_module cache_Ins_sram (
        .clk(clk),
        .write_enable   (put_sram_data.write_enable),
        .read_enable    (put_sram_data.read_enable),
        .set_index      (put_sram_data.index),
        .way_select     (put_sram_data.way),
        .write_data     (put_sram_data.write_data),
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
            if (read_enable) begin
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
            state <= FILL;      
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
        input integer index, way, data;
        begin
            put_sram_data.write_enable <= 1;
            put_sram_data.read_enable <= 0;
            put_sram_data.index <= index;
            put_sram_data.way <= way;
            put_sram_data.write_data <= data;
        end
    endtask
    
    task set_mem_request;
        input [31:0] address;
        begin
            mem_address <= address;
            mem_write_enable <= 0;
            mem_request <= 1;
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
            state <= IDLE;
            for (i = 0; i < NUM_SETS; i = i+1) begin
                for (j = 0; j < ASSOCIATIVITY; j = j+1) begin     
                    //set_sram_write_request(i, j, 0, 2);
                    cache_tags[i][j] <= 0;
                    valid[i][j] <= 0;
//                    lru_counter[i][j] <= j; // biased
                    lru_counter[i][j] <= 1; 
                end
            end
        end
    endtask

    task idle_state_logic;
        begin
            if ( read_enable) begin
                current_addr.address <= request_address;
                current_addr.tag     <= request_address[ADDR_WIDTH-1 -: TAG_WIDTH];
                current_addr.index   <= request_address[(ADDR_WIDTH - TAG_WIDTH - 1)-: INDEX_WIDTH];                   
                state <= CHECK_TAG;
            end
        end
    endtask

    task check_tag_logic;
        integer i;
        begin
            hit = 0;
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
 
    
    task fill_logic;
        begin  
            if (!mem_request) begin
                set_mem_request(current_addr.address);
            end else if (mem_ready) begin
                set_sram_write_request(current_addr.index, lru_way, mem_response_data);
                cache_tags[current_addr.index][lru_way] <= current_addr.tag;
                valid[current_addr.index][lru_way] <= 1;
                update_lru_counters(current_addr.index, lru_way);
                mem_request <= 0; 
                state <= CHECK_TAG; 
            end
        end
    endtask

    // Main Cache Operation 
    always @(posedge clk or negedge rstn) begin
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
                FILL: begin
                    fill_logic();
                    c_state <= 2; 
                end
                default: begin
                    idle_state_logic();
                    c_state <= 0; 
                end
            endcase
        end
    end   
endmodule
