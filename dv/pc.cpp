#include <catch2/catch_test_macros.hpp>
#include <VPC.h>
#include <cstdint>
#include <stdlib.h>


TEST_CASE("PC Test") {
  VPC model;
  uint32_t npc_input;

  for (int i = 0; i < 5000; i++) {
    npc_input = rand() % 4294967295;

    //test reset output
    model.rstn = 1;
    model.clk = 0;
    model.eval();
  
    model.rstn = 0;
    model.npc = npc_input;
    //model.pc_en = 1;
    model.eval();
    REQUIRE(model.pc == 0);
  
    model.clk = 1;
    model.eval();
    REQUIRE(model.pc == 0);
  
    //test PC
  
    model.rstn = 1;
    model.clk = 0;
    model.pc_en = 1;
    model.eval();

    model.clk = 1;
    model.npc = npc_input;
    model.eval();

    REQUIRE(model.pc == npc_input);

    model.clk = 0;
    model.eval();

    model.clk = 1;
    model.pc_en = 0;
    model.npc = rand() % 4294967295;
    model.eval();

    REQUIRE(model.pc == npc_input);
  }
}
