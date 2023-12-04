#include <catch2/catch_test_macros.hpp>
#include <VPipeline_Reset.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

/*
Note: 
The tests do not currently distinguish between High Z and 0 due to limitations of Verilator. 
The module could be modified to provide a test output that is 0 when rstn is 0 and 1 when rstn is High Z, 
but given the simplicity of this module that doesn't seem warrented at this point.
 */


TEST_CASE("flush == 0") { 
    VPipeline_Reset model;

    uint32_t npc_in;
    uint32_t npc_corr;
    
    for (int i = 0; i < 1000; i++) {
        npc_in = rand() % (int) (pow(2, 32));
        npc_corr = rand() % (int) (pow(2, 32));

        model.flush = 0;
        model.npc_in = npc_in;
        model.npc_corr = npc_corr;
        model.eval();

        REQUIRE((uint32_t) model.npc == (uint32_t) npc_in);
        REQUIRE(model.rstn_out == 0); //Verilator translates High Z outputs to 0 

    }
}

TEST_CASE("flush == 1") { 
    VPipeline_Reset model;

    uint32_t npc_in;
    uint32_t npc_corr;
    
    for (int i = 0; i < 1000; i++) {
        npc_in = rand() % (int) (pow(2, 32));
        npc_corr = rand() % (int) (pow(2, 32));

        model.flush = 1;
        model.npc_in = npc_in;
        model.npc_corr = npc_corr;
        model.eval();

        REQUIRE((uint32_t) model.npc == (uint32_t) npc_corr);
        REQUIRE(model.rstn_out == 0); //Expect actual 0 output here, not High Z

    }
}
