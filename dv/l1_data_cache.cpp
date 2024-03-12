#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VL1_Data_Cache.h>

struct sram {
    const std::uint32_t block_size = 4;
    const std::uint32_t cache_size = block_size * 1024;
    const std::uint32_t associativity = 2;
    const std::uint32_t block_width = block_size * 8;
    const std::uint32_t num_sets = cache_size / (block_size * associativity);
    const std::uint32_t addr_width = 32;

    std::uint32_t memory_array [num_sets * associativity]  = {0};
    std::uint32_t read_data = 0;
    
    void read (std::uint8_t set_index, bool way_select) {
        std::uint32_t act_adr = set_index * associativity + way_select;
        if (act_adr < (num_sets * associativity)) {
            read_data = memory_array[act_adr];
    }
    }

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

struct cache {
    const std::uint32_t block_size = 4;
    const std::uint32_t cache_size = block_size * 1024;
    const std::uint32_t associativity = 2;
    const std::uint32_t block_width = block_size * 8;
    const std::uint32_t num_sets = cache_size / (block_size * associativity);
    const std::uint32_t addr_width = 32;
    const std::uint32_t offset_width = log2(block_size);
    const std::uint32_t index_width = log2(num_sets);
    const std::uint32_t tag_width = addr_width - offset_width - index_width;

    std::uint32_t cache_tags [num_sets][associativity] = {0};
    bool valid [num_sets][associativity] = {0};
    bool dirty [num_sets][associativity] = {0};
    std::uint32_t lru_counter [num_sets] = {0};
    bool hit = 0;
    std::uint32_t way = 0;
    std::uint32_t lru_way = 0;
    bool sram_read_req = 0;
    std::uint32_t state = 0;

    struct current_address_t {
    std::uint32_t address;
    std::uint32_t tag;
    std::uint32_t index;
    std::uint32_t offset;
    current_address_t(std::uint32_t address, std::uint32_t tag, std::uint32_t index, std::uint32_t offset) : address(address), tag(tag), index(index), offset(offset) {} 
    };

    current_address_t current_addr(0, 0, 0, 0);

    std::uint32_t get_lru_way(std::uint32_t set_index) {
        std::uint32_t max_count = 0;
        lru_way = 0;
        for (int i {0}; i < associativity; ++i) {

        }
    }

};
struct ram {
    std::uint32_t data [pow(2, 32)]  = {0};
    bool ready = 1;
    std::uint32_t response_data = 0;
};

static void mem_logic(ram &mem, bool mem_request, bool mem_write_enable, std::uint32_t mem_write_data, std::uint32_t mem_address) {
    if (mem.ready) {
        if (mem_request) {
            if (mem_write_enable) mem.data[mem_address] = mem_write_data;
            else mem.response_data = mem.data[mem_address];
        }
    }
}

    
static void init(auto& l1) {
    l1.clk = 0;
    l1.rstn = 1;
    nyu::eval(l1);
    
    l1.clk = 0;
    l1.rstn = 0;
    nyu::eval(l1);
}

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

static void test_cache_read_hit(auto& l1, ram& mem, std::uint32_t request_address) {
    
    std::uint32_t result = cache_read(l1, mem, request_address)

    REQUIRE()

}



static ram mem;