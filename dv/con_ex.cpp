#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VCon_EX.h>

std::uint32_t calc_a (std::uint8_t a_sel, std::uint32_t rs1d, std::uint32_t pc_in) {
    if (a_sel == 0) return rs1d;
    else if (a_sel == 1) return pc_in;
    else return 0;
}

std::uint32_t calc_b (std::uint8_t b_sel, std::uint32_t rs2d, std::uint32_t imm) {
    if (b_sel == 0) return rs2d;
    else if (b_sel == 1) return imm;
    else if (b_sel == 2) return 4;
    else return imm << 12;
}

static void eval(auto& con_ex, std::uint8_t a_sel, std::uint8_t b_sel, bool branch_taken_in,  std::uint32_t imm,
    std::uint32_t pc_in, std::uint8_t rdn_in, std::uint32_t rs1d, std::uint32_t rs2d_in, std::uint32_t branch_addr_in,
    std::uint8_t alu_mode, std::uint32_t (*f)(std::uint32_t, std::uint32_t)) {

    uint32_t opA = calc_a(a_sel, rs1d, pc_in);
    uint32_t opB = calc_b(b_sel, rs2d_in, imm);

    INFO("Testing " << opA << " and " << opB);

    con_ex.clk = 0;
    con_ex.rstn = 1;
    nyu::eval(con_ex);

    con_ex.clk = 1;
    con_ex.rstn = 1;
    con_ex.a_sel = a_sel;
    con_ex.b_sel = b_sel;
    con_ex.branch_taken_in = branch_taken_in;
    con_ex.imm = imm;
    con_ex.pc_in = pc_in;
    con_ex.rdn_in = rdn_in;
    con_ex.rs1d = rs1d;
    con_ex.rs2d_in = rs2d_in;
    con_ex.branch_addr_in = branch_addr_in;
    con_ex.alu_mode = alu_mode;
    nyu::eval(con_ex);
    
    //Check Passthrough Values
    REQUIRE((bool) con_ex.branch_taken == (bool) branch_taken_in);
    REQUIRE((std::uint32_t) con_ex.pc == (std::uint32_t) pc_in);
    REQUIRE((std::uint32_t) con_ex.branch_addr == (std::uint32_t) branch_addr_in);
    REQUIRE((std::uint8_t) con_ex.rdn == (std::uint8_t) rdn_in);
    REQUIRE((std::uint32_t) con_ex.rs2d == (std::uint32_t) rs2d_in);

    std::uint32_t result {f(opA, opB)};

    REQUIRE(result == con_ex.alu_out);
} 

static void test(std::uint8_t alu_mode,
  std::uint32_t (*f)(std::uint32_t, std::uint32_t)) {
}

TEST_CASE("Con_EX, ADD") {
  test(0x00, [](std::uint32_t opA, std::uint32_t opB) { return opA + opB; });
}

TEST_CASE("Con_EX, SUB") {
  test(0x20, [](std::uint32_t opA, std::uint32_t opB) { return opA - opB; });
}

TEST_CASE("Con_EX, XOR") {
  test(0x04, [](std::uint32_t opA, std::uint32_t opB) { return opA ^ opB; });
}

TEST_CASE("Con_EX, OR") {
  test(0x06, [](std::uint32_t opA, std::uint32_t opB) { return opA | opB; });
}

TEST_CASE("Con_EX, AND") {
  test(0x07, [](std::uint32_t opA, std::uint32_t opB) { return opA & opB; });
}

TEST_CASE("Con_EX, LLS") {
  test(0x01,
      [](std::uint32_t opA, std::uint32_t opB) { return opA << (opB & 0x1F); });
}

TEST_CASE("Con_EX, LRS") {
  test(0x05,
      [](std::uint32_t opA, std::uint32_t opB) { return opA >> (opB & 0x1F); });
}

TEST_CASE("Con_EX, ARS") {
  test(0x25, [](std::uint32_t opA, std::uint32_t opB) {
    return (std::uint32_t)(((std::int32_t) opA) >> (opB & 0x1F));
  });
}

TEST_CASE("Con_EX, SSLT") {
  test(0x02, [](std::uint32_t opA, std::uint32_t opB) {
    return (std::uint32_t)(((std::int32_t) opA) < ((std::int32_t) opB));
  });
}

TEST_CASE("Con_EX, USLT") {
  test(0x03, [](std::uint32_t opA, std::uint32_t opB) {
    return (std::uint32_t)(opA < opB);
  });
}
