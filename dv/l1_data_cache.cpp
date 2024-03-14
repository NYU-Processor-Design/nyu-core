#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VL1_Data_Cache.h>

// Struct for Simulating Higher Level Memory
struct ram {
    std::uint32_t data [pow(2, 32)]  = {0};
    bool ready = 1;
    std::uint32_t response_data = 0;
};

// Function to Simulate Logic of Higher Level Memory
static void mem_logic(ram &mem, bool mem_request, bool mem_write_enable, std::uint32_t mem_write_data, std::uint32_t mem_address) {
    if (mem.ready) {
        if (mem_request) {
            if (mem_write_enable) mem.data[mem_address] = mem_write_data;
            else mem.response_data = mem.data[mem_address];
        }
    }
}

// Struct Corresponding to the SRAM Module That Stores the Cache Data
struct sram {
    const std::uint32_t block_size = 4;
    const std::uint32_t cache_size = block_size * 1024;
    const std::uint32_t associativity = 2;
    const std::uint32_t block_width = block_size * 8;
    const std::uint32_t num_sets = cache_size / (block_size * associativity);
    const std::uint32_t addr_width = 32;

    std::uint32_t memory_array [num_sets * associativity]  = {0};
    std::uint32_t read_data = 0;
    
    //Read Function for SRAM
    void read (std::uint8_t set_index, bool way_select) {
        std::uint32_t act_adr = set_index * associativity + way_select;
        if (act_adr < (num_sets * associativity)) {
            read_data = memory_array[act_adr];
    }
    }

    //Write Function for SRAM
    void write (std::uint8_t set_index, bool way_select, std::uint8_t data_mode, std::uint32_t write_data) {
        std::uint32_t act_adr = set_index * associativity + way_select;
        if (act_adr < (num_sets * associativity)) {
            switch(data_mode) {
                case 0: memory_array[act_adr] = (memory_array[act_adr] & 0xFFFFFF00) + (write_data & 0xFF);
                    break;
                case 1: memory_array[act_adr] = (memory_array[act_adr] & 0xFFFF0000) + (write_data & 0xFFFF);
                    break;
                default: memory_array[act_adr] = write_data;
            }
        }
    }
}

//Struct Corresponding to L1_Data_Cache Module
struct cache {

    //Various Cache Constants
    const std::uint32_t block_size = 4;
    const std::uint32_t cache_size = block_size * 1024;
    const std::uint32_t associativity = 2;
    const std::uint32_t block_width = block_size * 8;
    const std::uint32_t num_sets = cache_size / (block_size * associativity);
    const std::uint32_t addr_width = 32;
    const std::uint32_t offset_width = log2(block_size);
    const std::uint32_t index_width = log2(num_sets);
    const std::uint32_t tag_width = addr_width - offset_width - index_width;

    //Various Cache Variables
    std::uint32_t cache_tags [num_sets][associativity] = {0};
    bool valid [num_sets][associativity] = {0};
    bool dirty [num_sets][associativity] = {0};
    std::uint32_t lru_counter [num_sets] = {0};
    bool hit = 0;
    std::uint32_t way = 0;
    std::uint32_t lru_way = 0;
    bool sram_read_req = 0;
    std::uint32_t response_data = 0;
    sram cache_data;

    //Struct Outlining a Format Needed for the current_addr Cache Variable
    struct current_address_t {
    std::uint32_t address;
    std::uint32_t tag;
    std::uint32_t index;
    std::uint32_t offset;
    current_address_t(std::uint32_t address, std::uint32_t tag, std::uint32_t index, std::uint32_t offset) : address(address), tag(tag), index(index), offset(offset) {} 
    };
    current_address_t current_addr(0, 0, 0, 0);

    //Function to Update the lru_way Cache Variable
    std::uint32_t get_lru_way(std::uint32_t set_index) {
        std::uint32_t max_count = 0;
        lru_way = 0;
        for (int i {0}; i < associativity; ++i) {
            if (lru_counter[i] > max_count) {
                max_count = lru_counter[i];
                lru_way = i;
            }
        }
        return lru_way;
    }

    //Function to Handle Logic for a Cache Hit
    void handle_cache_hit(bool write_enable, bool read_enable, uint32_t write_data = 0, uint8_t data_mode = 0) {
        if (write_enable) {
            cache_data.write(current_addr.index, way, write_data, data_mode);
            dirty[current_addr.index][way] = 1;
        }
        else if (read_enable) {
            cache_data.read(current_addr.index, way);
            response_data = cache_data.read_data;
        }
    }

    //Function to Handle Logic for a Cache Miss
    void handle_cache_miss() {
        if (dirty[current_addr.index][lru_way]) {
            writeback_logic();
        }
        else fill_logic()
    }

    // Function to calculate the needed parameters from the requested data address
    void set_curr_addr(std::uint32_t request_addr) {
        current_addr.address = request_addr;

        //NEED TO FIGURE OUT HOW TO TRANSLATE VERILOG LOGIC
        current_addr.tag = request_addr & (); 
        current_addr.index = request_addr & (); 
        current_addr.offset = request_addr & (); 

    }

    //Function to Handle the Logic of Checking Data Tags
    void check_tag_logic(bool write_enable, bool read_enable, uint32_t write_data = 0, uint8_t data_mode = 0) {
        bool hit = 0;
        lru_way = get_lru_way(current_addr.index);
        for (int i {0}; i < associativity; ++i) {
            if (valid[current_addr.index][i] && cache_tags[current_addr.index][i] == current_addr.tag) {
                hit = 1;
                way = i;
                break;
            }
        }
        if (hit) handle_cache_hit(write_enable, read_enable, write_data, data_mode);
        else handle_cache_miss();
    }

    //Function to Handle the Write Back Logic
    void writeback_logic() {
        std::uint32_t writebrack_address = ;


    }

    //Function to Handle the Fill Logic
    void fill_logic()

    

};

//Function to Initialize the Cache
static void init(auto& l1) {
    l1.clk = 0;
    l1.rstn = 1;
    nyu::eval(l1);
    
    l1.clk = 0;
    l1.rstn = 0;
    nyu::eval(l1);
}

//Function to Handle Reading from the Cache
static std::uint32_t cache_read(auto& l1, ram &mem, std::uint32_t request_address) {
    l1.clk = 0;
    l1.rstn = 1;
    nyu::eval(l1);

    l1.clk = 1;
    l1.rstn = 1;
    l1.write_enable = 0;
    l1.read_enable = 1;
    l1.request_address = request_address;
    l1.mem_response_data = mem.response_data;
    l1.mem_ready = mem.ready;
    nyu::eval(l1);

    mem_logic(mem, l1.mem_request, l1.mem_write_enable, l1.mem_write_data, l1.mem_address);
    return l1.response_data;
}

//Function to Handle Writing to the Cache
static void cache_write(auto& l1, ram &mem, std::uint32_t request_address, std::uint32_t write_data, std::uint8_t data_mode) {
    l1.clk = 0;
    l1.rstn = 1;
    nyu::eval(l1);

    l1.clk = 1;
    l1.rstn = 1;
    l1.write_enable = 1;
    l1.read_enable = 0;
    l1.request_address = request_address;
    l1.write_data = write_data;
    l1.data_mode = data_mode;
    l1.mem_response_data = mem.response_data;
    l1.mem_ready = mem.ready;
    nyu::eval(l1);

    mem_logic(mem, l1.mem_request, l1.mem_write_enable, l1.mem_write_data, l1.mem_address);
}

//Function to Test the Behaviour of the Cache for a Read Hit
static void test_cache_read_hit(auto& l1, ram& mem, std::uint32_t request_address) {
    
    std::uint32_t result = cache_read(l1, mem, request_address)

    REQUIRE()

}



static ram mem;