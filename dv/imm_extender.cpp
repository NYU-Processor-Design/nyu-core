#include <catch2/catch_test_macros.hpp>
#include <VImm_extender.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>


uint32_t test(uint16_t imm) {
    VImm_extender model;
    model.imm = imm;
    model.eval();
    return model.out;
}


TEST_CASE("Positive Extension") {
for (int i = 0; i < 7500; i++) {
        uint16_t imm = (rand() % ((int) (pow(2, 12) - 1))) & ~(1 << 11);
        uint32_t result = test(imm);
        uint32_t result_upper = (result & (((int) (pow(2, 20) - 1)) << 11)) >> 11;
        uint32_t result_lower = (result & ((int) (pow(2, 12) - 1)));
        REQUIRE((result_upper == 0) & (result_lower == imm));
    }
}

TEST_CASE("Negative Extension") {
for (int i = 0; i < 7500; i++) {
        uint16_t imm = (rand() % ((int) (pow(2, 12) - 1))) | (1 << 11);
        uint32_t result = test(imm);
        uint32_t result_upper = (result & (((int) (pow(2, 20) - 1)) << 11)) >> 11;
        uint32_t result_lower = (result & ((int) (pow(2, 12) - 1)));
        REQUIRE((result_upper == (pow(2, 20) - 1)) & (result_lower == imm));
    }
}
