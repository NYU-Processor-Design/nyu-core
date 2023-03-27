#include <catch2/catch_test_macros.hpp>
#include <VBranch_EVal.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

bool test(uint32_t alu_out, uint8_t cond) {
    VBranch_Eval model;
    model.ALU_Out = alu_out;
    model.Cond = cond;
    model.eval();
    return model.out;
}

TEST_CASE("Never Branch") {  //Case when non branching instruction
 for (int i = 0; i < 1000; i++) {
        uint32_t alu_out = rand() % (int) (pow(2, 32) - 1);
        uint8_t cond = 0;
        bool result = test(alu_out, cond);
        REQUIRE(result == 0);
    }
}

TEST_CASE("Branch if ALU_OUT is Non-Zero") { //Case when branch condition is < or !=
    for (int i = 0; i < 1000; i++) {
        uint32_t alu_out = rand() % (int) (pow(2, 32) - 1);
        uint8_t cond = 1;
        bool result = test(alu_out, cond);
        REQUIRE(result == |alu_out);
    }
}


TEST_CASE("Branch if ALU_OUT is Zero") { //Case when branch condition is >= or =
    for (int i = 0; i < 1000; i++) {
        uint32_t alu_out = rand() % (int) (pow(2, 32) - 1);
        uint8_t cond = 1;
        bool result = test(alu_out, cond);
        REQUIRE(result == ~(|alu_out));
    }
}

TEST_CASE("Always Branch") { //Case when jump instruction
    for (int i = 0; i < 1000; i++) {
        uint32_t alu_out = rand() % (int) (pow(2, 32) - 1);
        uint8_t cond = 3;
        bool result = test(alu_out, cond);
        REQUIRE(result == 1);
    }
}