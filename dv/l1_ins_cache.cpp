#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <L1_Instruction_Cache.h>

const int BLOCK_SIZE = 4;
const int CACHE_SIZE = 1024; // 1 KB
const int ASSOCIATIVITY = 2;
const int NUM_SETS = CACHE_SIZE / (BLOCK_SIZE * ASSOCIATIVITY);
const int DATA_WIDTH = 32;
const int ADDR_WIDTH = 32;
const int INDEX_WIDTH = 7;
const int TAG_WIDTH = ADDR_WIDTH-INDEX_WIDTH;

struct ins_ram{
    std::uint32_t data[2048]={0};
    bool ready=1;
    std::uint32_t res_data=0;
    void read(uint32_t address){
        res_data=data[address];
    }
    void reset(){
        for(size_t i {0};i<2048;i++){
            data[i]=0;

        }
        res_data=0;
    }
};


class CacheSimulator {
public:
    std::vector<std::vector<uint32_t>> memory;
    std::vector<std::vector<bool>> valid_bits;
    std::vector<std::vector<uint32_t>> tags;
    std::vector<std::vector<int>> lru_counters;
    std::uint32_t output;
    CacheSimulator() {
        memory.resize(NUM_SETS, std::vector<uint32_t>(ASSOCIATIVITY, 0));
        valid_bits.resize(NUM_SETS, std::vector<bool>(ASSOCIATIVITY, false));
        tags.resize(NUM_SETS, std::vector<uint32_t>(ASSOCIATIVITY, 0));
        lru_counters.resize(NUM_SETS, std::vector<int>(ASSOCIATIVITY, 0));
    }

    void reset() {
        for (int i = 0; i < NUM_SETS; ++i) {
            for (int j = 0; j < ASSOCIATIVITY; ++j) {
                memory[i][j] = 0;
                valid_bits[i][j] = false;
                tags[i][j] = 0;
                lru_counters[i][j] = j; 
                //lru_counters[i][j] = 1;
            }
        }
    }

    void accessCache(uint32_t address, bool write,bool read, uint32_t write_data,ins_ram &mem) {
        uint32_t tag = address >> (ADDR_WIDTH-TAG_WIDTH);
        uint32_t index = address  & ((1 << INDEX_WIDTH) - 1);

        bool hit = false;
        int way = 0;

        // hit check
        for (int i = 0; i < ASSOCIATIVITY; ++i) {
            if (valid_bits[index][i] && tags[index][i] == tag) {
                hit = true;
                way = i;
                break;
            }
        }

        if (hit) {
            if (read) {
                output=memory[index][way];
            }
            updateLRU(index, way);
        } else {
            if (read) {
                way = findLRUWay(index);
                memory[index][way] = mem.data[address];
                tags[index][way] = tag;
                valid_bits[index][way] = true;
                updateLRU(index, way);
            }
        }
    }

private:

    uint32_t address;
    uint32_t tag;
    uint32_t index;

    int findLRUWay(int set_index) {
        int lru_way = 0, max_usage = 0;
        for (int i = 0; i < ASSOCIATIVITY; ++i) {
            if (lru_counters[set_index][i] > max_usage) {
                max_usage = lru_counters[set_index][i];
                lru_way = i;
            }
        }
        return lru_way;
    }

    void updateLRU(int set_index, int accessed_way) {
        for (int i = 0; i < ASSOCIATIVITY; ++i) {
            if (i == accessed_way) {
                lru_counters[set_index][i] = 0;
            } else {
                lru_counters[set_index][i]++;
            }
        }
    }
};

static void init(auto& L1) {
    L1.rstn = 0;
    L1.clk = 0;
    nyu::eval(L1);
    L1.rstn = 1;
    nyu::eval(L1);
}

static void read_eval(auto& L1, CacheSimulator& sim_cache, ins_ram& memory, std::uint32_t request_address) {
    // Set up initial conditions
    L1.read_enable = 1;
    L1.request_address = request_address;
    L1.mem_ready = 0;
    L1.mem_response_data = 0;
    L1.mem_request = 0;
    L1.mem_write_enable = 0;

    // De-assert read_enable after one cycle
    L1.clk = 1;
    nyu::eval(L1);
    L1.clk = 0;
    nyu::eval(L1);
    L1.read_enable = 0;

    bool response_valid = false;
    int max_cycles = 100; // prevent infinite loops
    int cycles = 0;
    uint32_t response_data = 0;

    while (!response_valid && cycles < max_cycles) {
        L1.clk = !L1.clk; // Toggle clock
        nyu::eval(L1);

        // Simulate memory interaction
        if (L1.mem_request) {
            // Simulate memory latency if needed
            L1.mem_ready = 1;
            L1.mem_response_data = memory.data[L1.mem_address];
        } else {
            L1.mem_ready = 0;
        }

        // Check if response_data is valid
        if (L1.c_state == 0 && !L1.read_enable && !L1.mem_request) {
            response_data = L1.response_data;
            response_valid = true;
        }

        cycles++;
    }

    // Use the CacheSimulator to get the expected output
    sim_cache.accessCache(request_address, /*write=*/false, /*read=*/true, /*write_data=*/0, memory);

    // Compare outputs
    REQUIRE(response_valid); // Ensure that we got a response
    REQUIRE(response_data == sim_cache.output);
}

// Test case using Catch2 framework
TEST_CASE("Cache read test") {
    // Create instances
    L1_Instruction_Cache L1;
    CacheSimulator sim_cache;
    ins_ram memory;

    // Initialize cache and memory
    init(L1);
    sim_cache.reset();
    memory.reset();

    // Initialize RAM with some data
    for (size_t i = 0; i < 2048; ++i) {
        memory.data[i] = i * 4; // Sample data
    }

    // Addresses to test
    std::uint32_t addresses[] = {0x00000000, 0x00000004, 0x00000008, 0x0000000C};

    for (auto address : addresses) {
        read_eval(L1, sim_cache, memory, address);
    }
}