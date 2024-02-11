#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VGPR.h>

static void write(auto& gpr, std::uint8_t rdn, std::uint32_t rdd, bool wbe) {
  gpr.clk = 0;
  gpr.rstn = 1;
  nyu::eval(gpr);

  //Write data rdd to register rdn if wbe is enabled
  gpr.clk = 1;
  gpr.rstn = 1;
  gpr.wbe = wbe;
  gpr.rdn = rdn;
  gpr.rdd = rdd;
  nyu::eval(gpr);
}

static (std::uint32_t, std::uint32_t) read(auto& gpr, std::uint8_t rs1n, std::uint8_t rs2n) {
  gpr.clk = 0;
  gpr.rstn = 1;
  nyu::eval(gpr);

  //Read data from registers rs1n and rs2n
  gpr.clk = 1;
  gpr.rstn = 1;
  gpr.wbe = 0;
  gpr.rs1n = rs1n;
  gpr.rs2n = rs2n;
  nyu::eval(gpr);
  return (gpr.rs1d, gpr.rs2d);
}

static void eval_rstn() {
  auto& gpr {nyu::getDUT<VGPR>()};
  for(std::uint8_t rdn {0}; rdn < 32; ++rdn)
    write(gpr, rdn, 0xFF, 1);

  gpr.clk = 0;
  gpr.rstn = 1;
  nyu::eval(gpr);

  gpr.clk = 0;
  gpr.rstn = 0;
  nyu::eval(gpr);

  for(std::uint8_t rs1n {0}; rs1n < 32; ++rs1n)
    REQUIRE(read(gpr, rs1n, 0)[0] == 0);
}

static void eval() {
  auto& gpr {nyu::getDUT<VGPR>()};

  

}

TEST_CASE("GPR, Reset") {

}

TEST_CASE("GPR, ") {

}