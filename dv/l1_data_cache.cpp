#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VL1_Data_Cache.h>

// Struct for Simulating Higher Level Memory
struct ram {
    std::uint32_t data [4294967296] = {0};
    bool ready = 1;
    std::uint32_t response_data = 0;

    // Function to Simulate Logic of Higher Level Memory
    void logic(bool mem_write_enable, std::uint32_t mem_write_data, std::uint32_t mem_address) {
        if (ready) {
            if (mem_write_enable) data[mem_address] = mem_write_data;
            else response_data = data[mem_address];
        }
    }
};

// Struct Corresponding to the SRAM Module That Stores the Cache Data
struct sram {
    static const std::uint32_t block_size = 4;
    static const std::uint32_t cache_size = block_size * 1024;
    static const std::uint32_t associativity = 2;
    static const std::uint32_t block_width = block_size * 8;
    static const std::uint32_t num_sets = cache_size / (block_size * associativity);
    static const std::uint32_t addr_width = 32;

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
};

//Struct Corresponding to L1_Data_Cache Module
struct cache {

    //Cache I/O
    std::uint32_t response_data = 0;

    //Various Cache Constants
    static const std::uint32_t block_size = 4;
    static const std::uint32_t cache_size = block_size * 1024;
    static const std::uint32_t associativity = 2;
    static const std::uint32_t block_width = block_size * 8;
    static const std::uint32_t num_sets = cache_size / (block_size * associativity);
    static const std::uint32_t addr_width = 32;
    static const std::uint32_t offset_width = 10;
    static const std::uint32_t index_width = 9;
    static const std::uint32_t tag_width = addr_width - offset_width - index_width;

    //Various Cache Variables
    std::uint32_t cache_tags [num_sets][associativity] = {0};
    bool valid [num_sets][associativity] = {0};
    bool dirty [num_sets][associativity] = {0};
    std::uint32_t lru_counter [num_sets][associativity] = {0};
    bool hit = 0;
    bool way = 0;
    bool lru_way = 0;
    std::uint32_t state = 0;
    sram cache_data;

    //Struct Outlining a Format Needed for the current_addr Cache Variable
    struct current_address_t {
        std::uint32_t address = 0;
        std::uint32_t tag = 0;
        std::uint32_t index = 0;
        std::uint32_t offset = 0;
        };
    current_address_t current_addr;

    //Function to Update the lru_way Cache Variable
    bool get_lru_way(std::uint32_t set_index) {
        std::uint32_t max_count = 0;
        lru_way = 0;
        for (size_t i {0}; i < associativity; ++i) {
            if (lru_counter[set_index][i] > max_count) {
                max_count = lru_counter[set_index][i];
                lru_way = i;
            }
        }
        return lru_way;
    }

    void update_lru_counters() {
        for (size_t i {0}; i < associativity; ++i) {
            if (i == way) lru_counter[current_addr.index][i] = 0;
            else if (lru_counter[current_addr.index][i] != (associativity - 1)) lru_counter[current_addr.index][i] += 1;
        }
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
        update_lru_counters();
    }

    //Function to Handle Logic for a Cache Miss
    void handle_cache_miss(ram &mem) {
        if (dirty[current_addr.index][lru_way]) {
            writeback_logic(mem);
        }
        else fill_logic(mem);
    }

    // Function to calculate the needed parameters from the requested data address
    void set_curr_addr(std::uint32_t request_addr) {
        current_addr.address = request_addr;
        current_addr.tag = request_addr >> (addr_width - tag_width); 
        current_addr.index = (request_addr >> (addr_width - tag_width - index_width)) & (std::uint32_t) (pow(2, index_width) - 1); 
        current_addr.offset = request_addr & (std::uint32_t) (pow(2, offset_width) - 1);
    }

    //Function to Handle the Logic of Checking Data Tags
    void check_tag_logic(ram &mem, bool write_enable, bool read_enable, uint32_t write_data = 0, uint8_t data_mode = 3) {
        bool hit = 0;
        lru_way = get_lru_way(current_addr.index);
        for (size_t i {0}; i < associativity; ++i) {
            if (valid[current_addr.index][i] && cache_tags[current_addr.index][i] == current_addr.tag) {
                hit = 1;
                way = i;
                break;
            }
        }
        if (hit) handle_cache_hit(write_enable, read_enable, write_data, data_mode);
        else handle_cache_miss(mem);
    }

    void writeback_logic(ram &mem) {
        std::uint32_t writeback_addr = (cache_tags[current_addr.index][lru_way] << (addr_width - tag_width)) + (current_addr.index << offset_width) + (pow(2, offset_width) - 1);
        cache_data.read(current_addr.index, way);
        mem.logic(1, cache_data.read_data, writeback_addr);
    }

    void fill_logic(ram &mem) {
        mem.logic(0, 0, current_addr.address);
        cache_data.write(current_addr.index, lru_way, mem.response_data, 2);
        cache_tags[current_addr.index][lru_way] = current_addr.tag;
        valid[current_addr.index][lru_way] = 1;
        dirty[current_addr.index][lru_way] = 0; 
        update_lru_counters();
    }

    void read(ram &mem, std::uint32_t addr) {
        set_curr_addr(addr);
        check_tag_logic(mem, 0, 1);
    }

    void write(ram &mem, std::uint32_t addr, std::uint32_t data, std::uint8_t data_mode = 3) {
        set_curr_addr(addr);
        check_tag_logic(mem, 1, 0, data, data_mode);
    }
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

    mem.logic(l1.mem_write_enable, l1.mem_write_data, l1.mem_address);
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

    mem.logic(l1.mem_write_enable, l1.mem_write_data, l1.mem_address);
}

//Function to Test the Behaviour of the Cache for a Read
static void eval_cache_read(auto& l1, ram& mem_sim, ram& mem_mod, cache& l1_sim, std::uint32_t request_address) {
    std::uint32_t result_mod = cache_read(l1, mem_mod, request_address);
    l1_sim.read(mem_sim, request_address);
    std::uint32_t result_sim = l1_sim.response_data;
    REQUIRE(result_mod == result_sim);
}

//Function to Test the Behaviour of the Cache for a Write
static void eval_cache_write(auto& l1, ram& mem_sim, ram& mem_mod, cache& l1_sim, std::uint32_t request_address, std::uint32_t write_data, std::uint8_t data_mode) {
    cache_write(l1, mem_mod, request_address, write_data, data_mode);
    l1_sim.write(mem_sim, request_address, write_data, data_mode);
    eval_cache_read(l1, mem_sim, mem_mod, l1_sim, request_address);
}

static void test_read(std::uint32_t data [4294967296]) {
    ram mem_sim;
    ram mem_mod;
    for (size_t i = 1; i < 4294967296; ++i) {
        mem_sim.data[i] = data[i];
        mem_mod.data[i] = data[i];
    }
    cache l1_sim;
    auto& l1 {nyu::getDUT<VL1_Data_Cache>()};
    init(l1);

    for(std::uint32_t addr {0}; addr < 2048; ++addr)
        eval_cache_read(l1, mem_sim, mem_mod, l1_sim, addr);

    for(std::uint32_t addr {1}; addr; addr <<= 1)
        eval_cache_read(l1, mem_sim, mem_mod, l1_sim, addr);
}

static void test_write(std::uint32_t mem_data [4294967296], std::uint32_t write_data [4294967296], std::uint8_t data_mode) {
    ram mem_sim;
    ram mem_mod;
    for (size_t i = 1; i < 4294967296; ++i) {
        mem_sim.data[i] = mem_data[i];
        mem_mod.data[i] = mem_data[i];
    }
    cache l1_sim;
    auto& l1 {nyu::getDUT<VL1_Data_Cache>()};
    init(l1);

    for(std::uint32_t addr {0}; addr < 2048; ++addr)
        eval_cache_write(l1, mem_sim, mem_mod, l1_sim, addr, write_data[addr], data_mode);
    
    for(std::uint32_t addr {1}; addr; addr <<= 1)
        eval_cache_write(l1, mem_sim, mem_mod, l1_sim, addr, write_data[addr], data_mode);
}

TEST_CASE("L1 Data Cache: Read") {
    std::uint32_t data [4294967296] = {0};

    //Add code to set up data values

    test_read(data);
}

TEST_CASE("L1 Data Cache: Write Bytes") {
    std::uint32_t mem_data [4294967296] = {0};
    std::uint32_t write_data [4294967296] = {0};

    //Add code to set up data values
    
    test_write(mem_data, write_data, 0);
}

TEST_CASE("L1 Data Cache: Write Halfs") {
    std::uint32_t mem_data [4294967296] = {0};
    std::uint32_t write_data [4294967296] = {0};

    //Add code to set up data values

    test_write(mem_data, write_data, 1);
}

TEST_CASE("L1 Data Cache: Write Words") {
    std::uint32_t mem_data [4294967296] = {0};
    std::uint32_t write_data [4294967296] = {0};

    //Add code to set up data values

    test_write(mem_data, write_data, 2);
}
