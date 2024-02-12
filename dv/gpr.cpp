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
    INFO("Testing Register " << rs1n);
    REQUIRE(read(gpr, rs1n, 0)[0] == 0);
}

static void eval(std::uint32_t[32] reg_vals, bool test_wbe) {
  auto& gpr {nyu::getDUT<VGPR>()};
  (std::uint32_t, std::uint32_t) read_vals;
  
  for(std::uint8_t rdn {0}; rdn < 32; ++rdn)
    write(gpr, rdn, reg_vals[rdn], 1);

  reg_vals[0] = 0;

  if(test_wbe) {
    for(std::uint8_t rdn {0}; rdn < 32; ++rdn)
      write(gpr, rdn, 0xFF, 0);
  }

  for(std::uint8_t rs1n {0}; rs1n < 32; ++rs1n)
    for(std::uint8_t rs2n {0}; rs2n < 32; ++rs2n) {
      read_vals = read(gpr, rs1n, rs2n);
      INFO("Testing rs1n = " << rs1n << ", rs2n = " << rs2n);
      REQUIRE(read_vals[0] == reg_vals[rs1n]);
      REQUIRE(read_vals[1] == reg_vals[rs2n]);
    }
}

TEST_CASE("GPR, Reset") {
  eval_rstn();
}

TEST_CASE("GPR, Write and Read") {
  

}

TEST_CASE("GPR, Disable Writing") {


}