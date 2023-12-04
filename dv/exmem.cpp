#include <catch2/catch_test_macros.hpp>
#include <VEXMEM.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

TEST_CASE("Reset"){
  VEXMEM model;
  bool clk;
  bool rstn;
  uint8_t rdn_in;
  uint32_t alu_out_in;
  uint32_t rs2d;

  for (int i = 0; i < 1000; i++) {
    rdn_in = rand() % (int) (pow(2,5));
    alu_out_in = rand() % (int) (pow(2,32));
    rs2d = rand() % (int) (pow(2,32));
    
    // initialize module
    model.rstn = 1;
    model.clk = 0;
    model.eval();

    model.clk = 1;
    model.rdn_in = rdn_in;
    model.alu_out_in = alu_out_in;
    model.rs2d = rs2d;
    model.eval();

    // test reset
    model.rstn = 0;
    model.eval();
    REQUIRE(model.rdn == 0);
    REQUIRE(model.alu_out == 0);
    REQUIRE(model.mem_data == 0);
  }
}

TEST_CASE("ExMem Latch") {
  VEXMEM model;
  bool clk;
  bool rstn;
  uint8_t rdn_in;
  uint32_t alu_out_in;
  uint32_t rs2d;
  bool branch_taken_in;

  for (int i = 0; i < 1000; i++) {
    rdn_in = rand() % (int) (pow(2,5));
    alu_out_in = rand() % (int) (pow(2,32));
    rs2d = rand() % (int) (pow(2,32));

    // reset module
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn = 0;
    model.eval();

    // set all registers
    model.rstn = 1;
    model.clk = 1;
    model.rdn_in = rdn_in;
    model.alu_out_in = alu_out_in;
    model.rs2d = rs2d;
    model.eval();
    REQUIRE(model.rdn == rdn_in);
    REQUIRE(model.alu_out == alu_out_in);
    REQUIRE(model.mem_data == rs2d);
  }
}
