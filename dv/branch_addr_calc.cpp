#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VBranch_Addr_Calc.h>


static void eval(bool mode, bool taken, std::uint32_t imm, std::uint32_t rs1d, std::uint32_t pc_in) {
    auto& bac {nyu::getDUT<VBranch_Addr_Calc>()};
    bac.addr_mode = mode;
    bac.branch_taken = taken;
    bac.imm = imm;
    bac.rs1d = rs1d;
    bac.pc_in = pc_in;
    nyu::eval(bac);

    INFO("Testing imm = " << imm << ", rs1d = " << rs1d << ", and pc_in = " << pc_in);
    
    if(mode) REQUIRE((uint32_t) bac.branch_addr == (uint32_t) (imm + rs1d));
    else REQUIRE((uint32_t) bac.branch_addr == (uint32_t) (pc_in + imm));

    if(taken) REQUIRE((uint32_t) bac.npc == (uint32_t) bac.branch_addr);
    else REQUIRE((uint32_t) bac.npc == (uint32_t) pc_in);

}

static void test(bool mode, bool taken) {
    for(std::uint32_t imm {0}; imm < 128; ++imm)
        for(std::uint32_t rs1d {0}; rs1d < 128; ++rs1d)
            for(std::uint32_t pc_in {0}; pc_in < 128; ++pc_in)
                eval(mode, taken, imm, rs1d, pc_in);
    
    for(std::uint32_t imm {1}; imm; imm <<= 1)
        for(std::uint32_t rs1d {1}; rs1d; rs1d <<= 1)
            for(std::uint32_t pc_in {1}; pc_in; pc_in <<= 1)
                eval(mode, taken, imm, rs1d, pc_in);
}


TEST_CASE("PC No Branch") {  //Case when branch_addr = pc + imm, but branch is not taken (addr mode 0, taken 0)
   test(0, 0);
}

TEST_CASE("PC Branch") { //Case when branch_addr = pc + imm, and branch is taken (addr mode 0, taken 1)
    test(0, 1);
}

TEST_CASE("RS1D No Branch") { //Case when branch_addr = imm + rs1d, but branch is not taken (addr mode 1, taken 0)
    test(1, 0);
}

TEST_CASE("RS1D Branch") { //Case when branch_addr = rs1d, and branch is taken (addr mode 1, taken 1)
   test(1, 1);
}