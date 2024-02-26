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

static std::pair<std::uint32_t, std::uint32_t> read(auto& gpr, std::uint8_t rs1n, std::uint8_t rs2n) {
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
  return std::make_pair(gpr.rs1d, gpr.rs2d);
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

  for(std::uint8_t rs1n {0}; rs1n < 32; ++rs1n) {
    INFO("Testing Register " << (int) rs1n);
    REQUIRE(read(gpr, rs1n, 0).first == 0);
  }
}

static void eval(std::uint32_t reg_vals[32], bool test_wbe) {
  auto& gpr {nyu::getDUT<VGPR>()};
  std::pair <std::uint32_t, std::uint32_t> read_vals;
  
  for(std::uint8_t rdn {0}; rdn < 32; ++rdn)
    write(gpr, rdn, reg_vals[rdn], 1);

  if(test_wbe) {
    for(std::uint8_t rdn {0}; rdn < 32; ++rdn)
      write(gpr, rdn, 0xFF, 0);
  }

  for(std::uint8_t rs1n {0}; rs1n < 32; ++rs1n)
    for(std::uint8_t rs2n {0}; rs2n < 32; ++rs2n) {
      read_vals = read(gpr, rs1n, rs2n);
      INFO("Testing rs1n = " << (int) rs1n << ", rs2n = " << (int) rs2n);
      REQUIRE(read_vals.first == reg_vals[rs1n] * (bool) rs1n);
      REQUIRE(read_vals.second == reg_vals[rs2n] * (bool) rs2n);
    }
}

TEST_CASE("GPR, Reset") {
  eval_rstn();
}

TEST_CASE("GPR, Write and Read") {
  std::uint32_t reg_vals[32] = {0};
  std::uint32_t zero_val;
 
  // Create inital set of register values
  for(int i {0}; i < 32; ++i)
    reg_vals[i] = 1 << i;

  // Test each bit of each register
  for(int i {0}; i < 32; ++i) {
    eval(reg_vals, 0);
    zero_val = reg_vals[0];
    for(int i {1}; i < 32; ++i) 
      reg_vals[i - 1] = reg_vals[i];
    reg_vals[31] = zero_val;
  }
}

TEST_CASE("GPR, Disable Writing") {
  std::uint32_t reg_vals[32] = {0};
  std::uint32_t zero_val;

  // Create inital set of register values
  for(int i {0}; i < 32; ++i)
    reg_vals[i] = 1 << i;

  // Test each bit of each register
  for(int i {0}; i < 32; ++i) {
    eval(reg_vals, 1);
    zero_val = reg_vals[0];
    for(int i {1}; i < 32; ++i) 
      reg_vals[i - 1] = reg_vals[i];
    reg_vals[31] = zero_val;
  }
}