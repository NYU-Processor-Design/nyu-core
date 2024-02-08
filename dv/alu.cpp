#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VAlu.h>

static void eval(std::uint8_t op, std::uint32_t opA, std::uint32_t opB,
    std::uint32_t (*f)(std::uint32_t, std::uint32_t)) {
  auto& alu {nyu::getDUT<VAlu>()};
  alu.alu_mode = op;
  alu.a = opA;
  alu.b = opB;
  nyu::eval(alu);

  std::uint32_t result {f(opA, opB)};
  INFO("Testing " << opA << " and " << opB);
  REQUIRE(result == alu.alu_out);
}

static void test(std::uint8_t op,
    std::uint32_t (*f)(std::uint32_t, std::uint32_t)) {
  for(std::uint32_t opA {0}; opA < 8; ++opA)
    for(std::uint32_t opB {0}; opB < 8; ++opB)
      eval(op, opA, opB, f);

  for(std::uint32_t opA {1}; opA; opA <<= 1)
    for(std::uint32_t opB {1}; opB; opB <<= 1)
      eval(op, opA, opB, f);
}

TEST_CASE("ALU, ADD") {
  test(0x00, [](std::uint32_t opA, std::uint32_t opB) { return opA + opB; });
}

TEST_CASE("ALU, SUB") {
  test(0x20, [](std::uint32_t opA, std::uint32_t opB) { return opA - opB; });
}

TEST_CASE("ALU, XOR") {
  test(0x04, [](std::uint32_t opA, std::uint32_t opB) { return opA ^ opB; });
}

TEST_CASE("ALU, OR") {
  test(0x06, [](std::uint32_t opA, std::uint32_t opB) { return opA | opB; });
}

TEST_CASE("ALU, AND") {
  test(0x07, [](std::uint32_t opA, std::uint32_t opB) { return opA & opB; });
}

TEST_CASE("ALU, LLS") {
  test(0x01,
      [](std::uint32_t opA, std::uint32_t opB) { return opA << (opB & 0x1F); });
}

TEST_CASE("ALU, LRS") {
  test(0x05,
      [](std::uint32_t opA, std::uint32_t opB) { return opA >> (opB & 0x1F); });
}

TEST_CASE("ALU, ARS") {
  test(0x25, [](std::uint32_t opA, std::uint32_t opB) {
    return (std::uint32_t)(((std::int32_t) opA) >> (opB & 0x1F));
  });
}

TEST_CASE("ALU, SSLT") {
  test(0x02, [](std::uint32_t opA, std::uint32_t opB) {
    return (std::uint32_t)(((std::int32_t) opA) < ((std::int32_t) opB));
  });
}

TEST_CASE("ALU, USLT") {
  test(0x03, [](std::uint32_t opA, std::uint32_t opB) {
    return (std::uint32_t)(opA < opB);
  });
}
