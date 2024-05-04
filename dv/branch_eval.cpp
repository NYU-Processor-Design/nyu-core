#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VBranch_Eval.h>

static void eval(uint8_t cond, std::uint32_t alu_out) {
    auto& beval {nyu::getDUT<VBranch_Eval>()};
    beval.alu_out = alu_out;
    beval.branch_cond = cond;
    nyu::eval(beval);

    INFO("Testing alu_out = " << alu_out);

    switch(cond) {
        case 0:
            REQUIRE((bool) beval.act_taken == 0);
            break;
        case 1:
            REQUIRE((bool) beval.act_taken == (bool) alu_out);
            break;
        case 2:
            REQUIRE((bool) beval.act_taken != (bool) alu_out);
            break;
        case 3:
            REQUIRE((bool) beval.act_taken == 1);
            break;
        default:
            break;
    }
}



static void test(std::uint8_t cond) {
    for(std::uint32_t alu_out {0}; alu_out < 2048; ++alu_out)
        eval(cond, alu_out);
    
    for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
        eval(cond, alu_out);
}

TEST_CASE("Branch Evaluator, Never Branch") {  //Case when non branching instruction
    test(0);
}

TEST_CASE("Branch Evaluator, Branch if ALU_OUT is Non-Zero") { //Case when branch condition is < or !=
    test(1);
}

TEST_CASE("Branch Evaluator, Branch if ALU_OUT is Zero") { //Case when branch condition is >= or =
    test(2);
}

TEST_CASE("Branch Evaluator, Always Branch") { //Case when jump instruction
   test(3);
}
