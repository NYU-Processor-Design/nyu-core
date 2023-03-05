#include <catch2/catch_test_macros.hpp>
#include <VAlu.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

uint32_t test(uint32_t a, uint32_t b, uint8_t op1, uint8_t op2) {
    VAlu model;
    model.op_code_1 = op1;
    model.op_code_2 = op2;
    model.operand_a = a;
    model.operand_b = b;
    model.eval();
    return model.out;
}

TEST_CASE("ADD") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0, 0);
        REQUIRE(result == (uint32_t) (a + b));
    }
}

TEST_CASE("SUB") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0, 1);
        REQUIRE(result == (uint32_t) (a + (~b + 1)));
    }
}

TEST_CASE("XOR") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 4, 0);
        REQUIRE(result == (a ^ b));
    }
}

TEST_CASE("OR") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 6, 0);
        REQUIRE(result == (a | b));
    }
}

TEST_CASE("AND") {
    for (int i = 0; i < 1000; i++) {
       uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 7, 0);
        REQUIRE(result == (a & b));
    }
}

TEST_CASE("LLS") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 1, 0);
        REQUIRE(result == (a << (b & 31)));
    }
}

TEST_CASE("LRS") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 5, 0);
        REQUIRE(result == (a >> (b & 31)));
    }
}

TEST_CASE("ARS") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 5, 1);
        uint32_t expected;
        if (a >> 31) {
            expected = (a >> (b & 31));
            for (int i = 32 - (b & 31); i < 32; i++) {
                expected += 1 << i;
            }
        }
        else {
        expected = (a >> (b & 31));
        }
        
        REQUIRE(result == expected);
    }
  
}

TEST_CASE("SSLT") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 2, 0);
        REQUIRE(result == (((a & (1 << 31)) & ~(b & (1 << 31)))? 1 : (~(a & (1 << 31)) & (b & (1 << 31))) ? 0 : a < b));
    }
}

TEST_CASE("USLT") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 3, 0);
        REQUIRE(result == (a < b));
    }
}