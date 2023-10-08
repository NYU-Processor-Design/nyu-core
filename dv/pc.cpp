#include <catch2/catch_test_macros.hpp>
#include <VPC.h>
#include <cstdint>
#include <stdlib.h>

TEST_CASE("PC Reset") {
  VPC model;
  uint32_t npc_input;

  for (int i = 0; i < 5000; i++) {
    npc_input = rand() % 4294967295;

    // testing PC reset
    // by setting the PC to a random input...
    
    model.rstn = 1;
    model.clk = 0;
    model.pc_en = 1;
    model.eval();

    model.clk = 1;
    model.npc = npc_input;
    model.eval();

    // then setting rstn to 0
    //model.clk = 0;
    //model.eval();
    //model.clk = 1;
    model.rstn = 0;
    model.eval();
    REQUIRE(model.pc == 0);
  }
}

TEST_CASE("PC Enable Disable") {
  VPC model;
  uint32_t npc_input;

  for (int i = 0; i < 5000; i++) {
    npc_input = rand() % 4294967295;

    // reset PC
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn = 0;
    model.eval();

    // enable PC input and set to random value
    model.rstn = 1;
    model.clk = 1;
    model.npc = npc_input;
    model.pc_en = 1;
    model.eval();
    REQUIRE(model.pc == npc_input);

    // disable PC input and try to set PC to another random value
    // output should equal old/previous input
    model.clk = 0;
    model.eval();
    model.clk = 1;
    model.pc_en = 0;
    model.npc = rand() % 4294967295;
    model.eval();
    REQUIRE(model.pc == npc_input);
  }
}
