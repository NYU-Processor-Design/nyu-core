#include <catch2/catch_test_macros.hpp>
#include <VGPR.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

TEST_CASE("REGS") {
  VGPRs model;
  uint8_t regsrc1, regsrc2;
  uint32_t dstdata;
  uint32_t regvals [32];
  
  for (int i = 0; i < 1000; i++) {
    //initialize
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn = 0;
    model.eval();
    
    for (int regdst = 0; regdst < 32; regdst++) {
      dstdata = rand() % (int) (pow(2,32) - 1);
      regvals[regdst] = dstdata;

      //write to all registers
      model.clk = 1;
      model.rstn = 1;
      model.wbe = 1;
      model.rdn = regdst;
      model.rdd = dstdata;
      model.eval();
    }
    
    // read two random registers
    regsrc1 = rand() % (int) 31;
    regsrc2 = rand() % (int) 31;
    model.wbe = 0;
    model.clk = 0;
    model.eval();
    
    model.clk = 1;
    model.rs1n = regsrc1;
    model.rs2n = regsrc2;
    model.eval();
    REQUIRE(model.rs1d == regvals[regsrc1]);
    REQUIRE(model.rs2d == regvals[regsrc2]);
  }
}
