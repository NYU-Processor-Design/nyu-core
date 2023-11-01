module L1_Data_Cache (
  input wire clk,
  input wire reset,
  input wire [31:0] address,
  input wire [31:0] data_in,
  input wire write_enable,
  output wire [31:0] data_out,
  output wire hit
);

  // Cache parameters
  parameter CACHE_SIZE = 16 * 1024;  // 16 KB
  parameter BLOCK_SIZE = 32;         // 32 bytes
  parameter SETS = CACHE_SIZE / (BLOCK_SIZE * 4);  // Number of sets
  parameter ASSOCIATIVITY = 4;       // 4-way set-associative
  parameter TAG_WIDTH = $clog2(SETS);             // Calculate TAG_WIDTH based on the number of sets
  parameter INDEX_WIDTH = $clog2(SETS / ASSOCIATIVITY);  // Calculate INDEX_WIDTH

  // Cache memory
  reg [31:0] cache_data [0:SETS-1][0:ASSOCIATIVITY-1];
  reg [TAG_WIDTH-1:0] cache_tags [0:SETS-1][0:ASSOCIATIVITY-1];
  reg [ASSOCIATIVITY-1:0] valid [0:SETS-1];

  // LRU priority encoder
  wire [ASSOCIATIVITY-1:0] lru_way;
  LRU_Priority_Encoder #(ASSOCIATIVITY) lru_encoder (
    .valid(valid[address[INDEX_WIDTH + BLOCK_SIZE - 1: BLOCK_SIZE]]),
    .priority(lru_way)
  );

  // Cache hit/miss logic
  wire hit = 1'b0;
  generate
    if (ASSOCIATIVITY > 1) begin : set_assoc
      wire [ASSOCIATIVITY-1:0] hit_lines;
      generate
        for (genvar i = 0; i < SETS; i = i + 1) begin : set_loop
          assign hit_lines = (cache_tags[i] == address[TAG_WIDTH + INDEX_WIDTH - 1: INDEX_WIDTH]);
          assign hit = hit | (valid[i][lru_way] & hit_lines[lru_way]);
        end
      endgenerate
    end else begin
      assign hit = valid[address[INDEX_WIDTH + BLOCK_SIZE - 1: BLOCK_SIZE]] & (cache_tags[address[INDEX_WIDTH + BLOCK_SIZE - 1: BLOCK_SIZE]] == address[TAG_WIDTH + INDEX_WIDTH - 1: INDEX_WIDTH]);
    end
  endgenerate

  // Data output logic
  assign data_out = (hit) ? cache_data[address[INDEX_WIDTH + BLOCK_SIZE - 1: BLOCK_SIZE]][lru_way] : 32'b0;

  // Write cache logic
  always @(posedge clk) begin
    if (reset) begin
      for (int i = 0; i < SETS; i = i + 1) begin
        for (int j = 0; j < ASSOCIATIVITY; j = j + 1) begin
          cache_data[i][j] <= 32'b0;
          cache_tags[i][j] <= 32'b0;
          valid[i][j] <= 1'b0;
        end
      end
    end else begin
      if (write_enable & hit) begin
        cache_data[address[INDEX_WIDTH + BLOCK_SIZE - 1: BLOCK_SIZE]][lru_way] <= data_in;
      end
    end
  end

endmodule


//===========================================================


module L1_data_cache(

    input clk, reset, write_enable,
    input [31:0] request_address, write_data,
    output reg [31:0] response_data
);
    // Cache Configuration
    parameter ADDRESS_WIDTH       = 32;                                               // Total address width
    parameter CACHE_SIZE          = 16 * 1024;                                        // Cache size in bytes
    parameter BLOCK_SIZE          = 32;                                               // Block size in bytes
    parameter ASSOCIATIVITY       = 4;                                                // Associativity
    parameter BLOCK_OFFSET_BITS   = $clog2(BLOCK_SIZE);                               // Block offset bits
    parameter NO_OF_SETS          = CACHE_SIZE / (BLOCK_SIZE * ASSOCIATIVITY);        // Number of sets
    parameter INDEX_WIDTH         = $clog2(NO_OF_SETS);                                     // Index width
    parameter TAG_WIDTH           = ADDRESS_WIDTH - (BLOCK_OFFSET_BITS + INDEX_WIDTH);// Tag width
    
    reg [31:0] cache_data [0:NO_OF_SETS -1][0: ASSOCIATIVITY -1];
    reg [TAG_WIDTH -1:0] cache_tags [0:NO_OF_SETS -1][0: ASSOCIATIVITY -1];
    reg [ASSOCIATIVITY -1:0] valid [0:NO_OF_SETS -1];
    
    reg [1:0] lru_counter [0: NO_OF_SETS -1][0: ASSOCIATIVITY -1];
    reg dirty_bit[0: NO_OF_SETS][0: ASSOCIATIVITY-1];
    
    // Helper function to find the least recently used block in a set NOT AUTOMAIC (blocking)
    // automatic fucntion is non blocking, non automatics are blocking
    function integer get_lru_block(
    
        input [ASSOCIATIVITY-1:0] lru_set
    );
        integer lru_block_index, i, min_lru_value;
        begin 
        
            lru_block_index = 0;
            min_lru_value = lru_set[0];
            
            for (i = 1; i < ASSOCIATIVITY; i = i + 1) begin
                if (lru_set[i] < min_lru_value) begin
                    lru_block_index = i;
                    min_lru_value = lru_set[i];
                end
            end
            get_lru_block = lru_block_index;
        end
    endfunction
    
    // Helper function to write data to the main memory
    function write_to_memory;
        input [31:0] memory_address;
        input [31:0] data_to_write;
        // Implement memory write operation
    endfunction
    
    // Helper function to read data from the main memory on cache miss
    function [31:0] read_from_memory;
        input [31:0] memory_address;
        // Implement memory read operation
        // Return data read from memory
    endfunction

    reg [NO_OF_SETS -1:0] set_index;
    reg [ASSOCIATIVITY -1:0] lru_index;
    
    always @(posedge clk) begin
        if (reset) begin
            for (set_index = 0; set_index < NO_OF_SETS; set_index = set_index + 1) begin
                for (lru_index = 0; lru_index < ASSOCIATIVITY; lru_index = lru_index + 1) begin
                    lru_counter[set_index][lru_index] <= 2'b11;
                    dirty_bit[set_index][lru_index] <= 1'b0;
                end
            end
        end else if (write_enable) begin
            set_index = (request_address / BLOCK_SIZE) % NO_OF_SETS;
            lru_index = get_lru_block(lru_counter[set_index]);
            if (tag[set_index][lru_index] == request_address[block_size+log2(num_sets)-1:log2(block_size)]) begin
                cache_data[set_index][lru_index] <= write_data;
                dirty_bit[set_index][lru_index] <= 1'b1;
                lru_counter[set_index][lru_index] <= 2'b00;
            end else begin
                if (dirty_bit[set_index][lru_index]) begin
                    // Write back to main memory before replacing the block
                    write_to_memory(tag[set_index][lru_index], cache_data[set_index][lru_index]);
                end
                tag[set_index][lru_index] <= request_address[block_size+log2(num_sets)-1:log2(block_size)];
                cache_data[set_index][lru_index] <= write_data;
                dirty_bit[set_index][lru_index] <= 1'b1;
                lru_counter[set_index][lru_index] <= 2'b00;
            end
        end else begin
            set_index = (request_address / block_size) % num_sets;
            for (lru_index = 0; lru_index < num_blocks; lru_index = lru_index + 1) begin
                if (tag[set_index][lru_index] == request_address[block_size+log2(num_sets)-1:log2(block_size)]) begin
                    response_data <= cache_data[set_index][lru_index];
                    lru_counter[set_index][lru_index] <= 2'b00;
                end else begin
                    lru_counter[set_index][lru_index] <= lru_counter[set_index][lru_index] - 1'b01;
                end
            end
    
            // Fetch from main memory on cache miss
            if (response_data === 32'hx) begin
                response_data <= read_from_memory(request_address);
                // Implement write allocate if necessary
            end
        end
    end   
endmodule




   // ----------Define a stack for each set to track LRU order------------
   reg [ASSOCIATIVITY-1:0] lru_stack [0:SETS-1];
   integer set;
    
   // Initialize the stack to a default order (0, 1, 2, 3, ...)
   always @(posedge clk or posedge reset) begin
       if (reset) begin
           for (set = 0; set < SETS; set = set + 1) begin
               lru_stack[set] <= set;
           end
       end
   end
    
   // Function to get the index of the least recently used line and update the LRU stack
   function automatic integer getAndUpdateLRU(
    
       input integer set_index,
       input integer accessed_line
   );
       integer lru_index, i;
       begin
           // Find the LRU line index
           for (i = 0; i < ASSOCIATIVITY; i = i + 1) begin
               if (lru_stack[set_index][i] == 'd0) begin
                   lru_index = i;
                   break;
               end
           end
            
           // Update the LRU stack by moving the accessed line to the most recently used position
           lru_stack[set_index] = {lru_stack[set_index][lru_index+1:0], accessed_line};
            
           getAndUpdateLRU = lru_index;
       end
   endfunction



// LRU function to determine the way (associativity) to replace
function [ASSOCIATIVITY-1:0] lru_way;
    input [1:0] set_index;
    input [ASSOCIATIVITY-1:0] valid_bits;
    input [1:0] access_way;

    reg [ASSOCIATIVITY-1:0] lru_counts;
    reg [1:0] min_count;
    reg [ASSOCIATIVITY-1:0] least_recently_used;

    // Initialize the least recently used way with 0
    initial begin
        least_recently_used = 0;
    end

    // Calculate the LRU way for the given set
    always @* begin
        lru_counts = lru_counter[set_index];
        min_count = 2'b11; // Initialize with maximum counter value

        // Iterate through each way to find the least recently used one
        for (i = 0; i < ASSOCIATIVITY; i = i + 1) begin
            if (valid_bits[i] && (lru_counts[i] < min_count)) begin
                min_count = lru_counts[i];
                least_recently_used = i;
            end
        end
    end

    // Update the LRU counters when a cache way is accessed
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            // Reset the LRU counters on a global reset
            lru_counter[set_index] <= 0;
        end else if (valid_bits[access_way]) begin
            // Increment the counter for the accessed way and decrement others
            // lru_counter[set_index] = lru_counter[set_index] + (lru_counts == access_way);
            lru_counter[set_index] = lru_counts + 1'b1 << access_way;

        end
    end

    // Return the least recently used way
    assign lru_way = least_recently_used;
endfunction
