#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VPC.h>

static void eval_reset (std::uint32_t npc) {
   auto& pc {nyu::getDUT<VPC>()};
   
    // testing PC reset
    // by setting the PC to a value...
    pc.rstn = 1;
    pc.clk = 0;
    pc.pc_en = 1;
    nyu::eval(pc);

    pc.clk = 1;
    pc.npc = npc;
    nyu::eval(pc);

    // then setting rstn to 0
    pc.rstn = 0;
    nyu::eval(pc);
    REQUIRE(pc.pc == 0);
  
}

TEST_CASE("PC Reset") {
  
  for(std::uint32_t npc {0}; npc < 512; ++npc)
    eval_reset(npc);
  
  for(std::uint32_t npc {1}; npc; npc <<= 1)
    eval_reset(npc);
 
}

static void eval_en (std::uint32_t npc) {
   auto& pc {nyu::getDUT<VPC>()};
   
   // reset PC
    pc.rstn = 1;
    pc.clk = 0;
    nyu::eval(pc);
    pc.rstn = 0;
    nyu::eval(pc);

    // enable PC input and set to  value
    pc.rstn = 1;
    pc.clk = 1;
    pc.npc = npc;
    pc.pc_en = 1;
    nyu::eval(pc);
    REQUIRE(pc.pc == npc);

    // disable PC input and try to set PC to another value
    // output should equal old/previous input
    pc.clk = 0;
    nyu::eval(pc);
    pc.clk = 1;
    pc.pc_en = 0;
    pc.npc = npc + npc + 1;
    nyu::eval(pc);
    REQUIRE(pc.pc == npc);
  
}

TEST_CASE("PC Enable Disable") {
  for(std::uint32_t npc {0}; npc < 512; ++npc)
    eval_en(npc);
  
  for(std::uint32_t npc {1}; npc; npc <<= 1)
    eval_en(npc);

}
