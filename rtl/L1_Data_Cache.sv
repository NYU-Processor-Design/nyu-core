// Write HIT:  Write-back: In a write-back cache, data is written to the cache and only later to the main memory when the cache line is replaced. 
// Write MISS: Write allocate: when a write miss occurs, the cache line is loaded into the cache, and then the write operation is performed.
// Look-through:  which means it checks the main memory for cache misses.
// LRU (Least Recently Used):  which means the least recently used cache line is selected for replacement.

module L1_data_cache #(

    parameter ADDRESS_LENGTH      = 32,                                              
    parameter CACHE_SIZE          = 16 * 1024,                                       
    parameter BLOCK_SIZE          = ADDRESS_LENGTH,                                              
    parameter ASSOCIATIVITY       = 4     
)(

    input clk, reset, write_enable,
    input [31:0] request_address, write_data,
    output reg [31:0] response_data
);
    // Cache Configuration
                                           
    localparam BLOCK_WIDTH         = $clog2(BLOCK_SIZE);                               
    localparam NO_OF_SETS          = CACHE_SIZE / (BLOCK_SIZE * ASSOCIATIVITY);        
    localparam INDEX_WIDTH         = $clog2(NO_OF_SETS);                                  
    localparam TAG_WIDTH           = ADDRESS_LENGTH - (BLOCK_WIDTH + INDEX_WIDTH);
    
    //cache data arrays
//    reg [31:0] cache_data [0:NO_OF_SETS-1][0:ASSOCIATIVITY-1][0:BLOCK_SIZE/4-1];
    reg [31:0] cache_data [0:NO_OF_SETS-1][0:ASSOCIATIVITY-1];
    reg [TAG_WIDTH - 1:0] cache_tags [0:NO_OF_SETS-1][0:ASSOCIATIVITY-1];
    reg [ASSOCIATIVITY-1:0] valid [0: NO_OF_SETS-1];
    reg [ASSOCIATIVITY-1:0] dirty [0: NO_OF_SETS-1];
    reg [ASSOCIATIVITY-1:0] lru_counter [0: NO_OF_SETS-1];
    
    // Helper function to find the least recently used block in a set NOT AUTOMAIC (blocking)
    // automatic fucntion is non blocking, non automatics are blocking
    function integer get_lru_way(input integer set_index);
        integer lru_way = 0;
        begin
            for (integer i = 0; i < ASSOCIATIVITY; i++) begin
                if (lru_counter[set_index][i] < lru_counter[set_index][lru_block])
                    lru_way = i;
            end

            return lru_way;
        end
    endfunction

    
    
    integer set;
    integer way;
    integer hit_way = -1;
    
    always @(posedge clk) begin 
    
        if (reset) begin
            for (set = 0; set < NO_OF_SETS; set = set + 1) begin
                for (way = 0; way < ASSOCIATIVITY; way = way + 1) begin
                    lru_counter[set][way] <= way; // Initialize the LRU counter to ascending values
                    dirty [set][way] <= 'd0;
                end
            end
        end 
        
        
        else if(write_enable) begin 
            set = (request_address / BLOCK_SIZE) % NO_OF_SETS;
            way = get_lru_block(lru_counter[set]);
            if(cache_tags[set][way] == request_address [31: 32- TAG_WIDTH]) begin
                cache_data[set][way] <= write_data;
                dirty[set][way] <= 1'b1;
                lru_counter[set][way] <= 'd0;
            end 
            else begin
                // Determine the set and way based on the request address
                set = (request_address / BLOCK_SIZE) % NO_OF_SETS;
                way = get_lru_block(lru_counter[set]);
                
                // Check if the cache line is dirty
                if (dirty[set][way]) begin
                
                    // --->>Write the cache data back to the main memory at the corresponding address
                
//                    main_memory[cache_tags[set][way]] <= cache_data[set][way];
                    dirty[set][way] <= 1'b0; // Mark as not dirty after write-back
                end
                
                // Update the cache with the new data and mark as dirty
                cache_data[set][way] <= write_data;
                dirty[set][way] <= 1'b1;
                lru_counter[set][way] <= 'd0;
            end

        end
        
        
        else begin
            set = (request_address / BLOCK_SIZE) % NO_OF_SETS;
        
            // Find the hit way if it exists
            for (way = 0; way < ASSOCIATIVITY; way = way + 1) begin
                if (cache_tags[set][way] == request_address[31:32 - TAG_WIDTH]) begin
                    response_data <= cache_data[set][way];
                    lru_counter[set][way] <= 'd0;
                    hit_way = way;
                end
            end
        
            // Handle cache miss
            if (hit_way == -1) begin
//                 Here, you would typically fetch the data from a higher-level memory (e.g., main memory) and update the cache.
//                 You would also update cache_tags, cache_data, and LRU counters.
                
//                 For simplicity, let's assume you have fetched the data from memory and now need to update the cache.
        
//                 Set the LRU counter for the way that will receive the new data to 0 (it's the most recently used).
//                lru_counter[set][way_to_replace] <= 'd0;
        
//                 Update cache_tags with the new tag for the way that received the data.
//                cache_tags[set][way_to_replace] <= request_address[31:32 - TAG_WIDTH];
        
//                 Update cache_data with the fetched data.
//                cache_data[set][way_to_replace] <= fetched_data;
                
//                 Now, way_to_replace holds the index of the way that received the new data.
//                response_data <= fetched_data;
            end
        
            // Update LRU counters for other ways in the set
            for (way = 0; way < ASSOCIATIVITY; way = way + 1) begin
                if (way != hit_way) begin
                    if (lru_counter[set][way] < lru_counter[set][hit_way]) begin
                        lru_counter[set][way] <= lru_counter[set][way] + 1;
                    end
                end
            end
        end
        
    
    end    
endmodule


