#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VEXMEM.h>

static void eval(std::uint8_t rdn_in, std::uint32_t alu_out_in, 
std::uint32_t rs2d, bool reset) {
  
  auto& exmem {nyu::getDUT<VEXMEM>()};
  
  // Initialize Module
  exmem.rstn = 1;
  exmem.clk = 0;
  nyu::eval(exmem);

  nyu::eval(exmem);
  exmem.rstn = 0;
    nyu::eval(exmem);

  // Test
  exmem.clk = 1;
  exmem.rstn = 1;
  exmem.rdn_in = rdn_in;
  exmem.alu_out_in = alu_out_in;
  exmem.rs2d = rs2d;
  nyu::eval(exmem);

  if (reset) {
    exmem.rstn = 0;
    nyu::eval(exmem);
  }

  INFO("Testing rdn_in = " << rdn_in << ", alu_out_in = " << alu_out_in << ", and rs2d = " << (int) rs2d);

  if (reset) {
  REQUIRE(exmem.rdn == 0);
  REQUIRE(exmem.alu_out == 0);
  REQUIRE(exmem.mem_data == 0);
  }

  else {
  REQUIRE(exmem.rdn == rdn_in);
  REQUIRE(exmem.alu_out == alu_out_in);
  REQUIRE(exmem.mem_data == rs2d);
  }

}

static void test(bool reset) {
  for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
    for(std::uint32_t alu_out_in {0}; alu_out_in < 64; ++alu_out_in)
      for(std::uint32_t rs2d {0}; rs2d < 32; ++rs2d)
        eval(rdn_in, alu_out_in, rs2d, reset);

  for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
    for(std::uint32_t alu_out_in {1}; alu_out_in; alu_out_in <<= 1)
      for(std::uint32_t rs2d {1}; rs2d; rs2d <<= 1)
        eval(rdn_in, alu_out_in, rs2d, reset);
}


TEST_CASE("EXMEM, Reset"){
  test(1);
}

TEST_CASE("EXMEM, Latch Passthrough") {
  test(0);
}
