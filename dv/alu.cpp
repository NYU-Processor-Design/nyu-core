#include <catch2/catch_test_macros.hpp>
#include <VAlu.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

uint32_t test(uint32_t a, uint32_t b, uint8_t op) {
    VAlu model;
    model.alu_mode = op;
    model.a = a;
    model.b = b;
    model.eval();
    return model.alu_out;
}

TEST_CASE("ADD") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x0);
        REQUIRE(result == (uint32_t) (a + b));
    }
}

TEST_CASE("SUB") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x10);
        REQUIRE(result == (uint32_t) (a + (~b + 1)));
    }
}

TEST_CASE("XOR") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x04);
        REQUIRE(result == (a ^ b));
    }
}

TEST_CASE("OR") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x06);
        REQUIRE(result == (a | b));
    }
}

TEST_CASE("AND") {
    for (int i = 0; i < 1000; i++) {
       uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x07);
        REQUIRE(result == (a & b));
    }
}

TEST_CASE("LLS") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x01);
        REQUIRE(result == (a << (b & 31)));
    }
}

TEST_CASE("LRS") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x05);
        REQUIRE(result == (a >> (b & 31)));
    }
}

TEST_CASE("ARS") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x15);
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
        uint32_t result = test(a, b, 0x02);
        REQUIRE(result == (((a & (1 << 31)) & ~(b & (1 << 31)))? 1 : (~(a & (1 << 31)) & (b & (1 << 31))) ? 0 : a < b));
    }
}

TEST_CASE("USLT") {
    for (int i = 0; i < 1000; i++) {
        uint32_t a = rand() % (int) (pow(2, 32) - 1);
        uint32_t b = rand() % (int) (pow(2, 32)  - 1);
        uint32_t result = test(a, b, 0x03);
        REQUIRE(result == (a < b));
    }
}