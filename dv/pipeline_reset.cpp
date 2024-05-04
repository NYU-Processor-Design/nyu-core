#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VPipeline_Reset.h>


/*
Note: 
The tests do not currently distinguish between High Z and 0 due to limitations of Verilator. 
The module could be modified to provide a test output that is 0 when rstn is 0 and 1 when rstn is High Z, 
but given the simplicity of this module that doesn't seem warranted at this point.
 */

static void eval(std::uint32_t npc_in, std::uint32_t npc_corr, bool flush) {
    auto& pipe {nyu::getDUT<VPipeline_Reset>()};
    pipe.npc_in = npc_in;
    pipe.npc_corr = npc_corr;
    pipe.flush = flush;
    nyu::eval(pipe);

    INFO("Testing npc_in = " << npc_in << "and npc_corr = " << npc_corr);
    
    if(!flush) {
        REQUIRE((uint32_t) pipe.npc == (uint32_t) npc_in);   
        REQUIRE(pipe.rstn_out == 0); //Verilator translates High Z outputs to 0 
    }

    else {
        REQUIRE((uint32_t) pipe.npc == (uint32_t) npc_corr);
        REQUIRE(pipe.rstn_out == 0); //Expect actual 0 output here, not High Z
    }
}

static void test(bool flush) {
    for(std::uint32_t npc_in {0}; npc_in < 128; ++npc_in)
    for(std::uint32_t npc_corr {0}; npc_corr < 128; ++npc_corr)
      eval(npc_in, npc_corr, flush);

  for(std::uint32_t npc_in {1}; npc_in; npc_in <<= 1)
    for(std::uint32_t npc_corr {1}; npc_corr; npc_corr <<= 1)
      eval(npc_in, npc_corr, flush);
}

TEST_CASE("Pipeline Reset, flush == 0") { 
    test(0);
}

TEST_CASE("Pipeline Reset, flush == 1") { 
    test(1);
}
