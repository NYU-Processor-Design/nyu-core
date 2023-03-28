#include <catch2/catch_test_macros.hpp>
#include <VPC.h>
#include <cstdint>
#include <stdlib.h>

TEST_CASE("PC Test") {
  VPC model;
  
  //test reset output
  model.rstn = 1;
  model.clk = 0;
  model.eval();
  
  model.rstn = 0;
  model.npc = npc_input;
  model.eval();
  REQUIRE(model.pc == 0);
  
  model.clk = 1;
  model.eval();
  REQUIRE(model.pc == 0);
  
  //test PC
  
  model.rstn = 1;
  
  for (size_t i = 0; i < 5000; i++) {
    model.clk = 0;
    model.eval();

    model.clk = 1;
    model.npc = npc_input;
    model.eval();

    REQUIRE(model.pc == npc_input);
  }
}
