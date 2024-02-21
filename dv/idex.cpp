#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VIDEX.h>

static void eval(auto& idex, std::uint8_t a_sel, std::uint8_t b_sel,  bool branch_taken_in, std::uint8_t rdn_in,
    std::uint32_t pc_in, std::uint32_t imm, std::uint32_t rs1d, std::uint32_t rs2d_in, std::uint32_t branch_addr_in) {
    idex.clk = 0;
    idex.rstn = 1;
    nyu::eval(idex);

    idex.clk = 1;
    idex.rstn = 1;
    idex.branch_taken_in = branch_taken_in;
    idex.a_sel = a_sel;
    idex.b_sel = b_sel;
    idex.rdn_in = rdn_in;
    idex.pc_in = pc_in;
    idex.imm = imm;
    idex.rs1d = rs1d;
    idex.rs2d_in = rs2d_in;
    idex.branch_addr_in = branch_addr_in;
    nyu::eval(idex);

    INFO("Testing a_sel = " << (int) a_sel << ", b_sel = " << (int) b_sel << ", branch_taken_in = " << branch_taken_in << ", rdn_in = " << (int) rdn_in << ", pc_in = " << pc_in << ", imm = " << imm << ", rs1d = " << rs1d << ", rs2d_in = " << rs2d_in << ", and branch_addr_in = " << branch_addr_in);
    
    // Test passthrough
    REQUIRE((std::uint32_t) idex.pc == (std::uint32_t) pc_in);
    REQUIRE((std::uint8_t) idex.rdn == (std::uint8_t) rdn_in);
    REQUIRE((bool) idex.branch_taken == (bool) branch_taken_in);
    REQUIRE((std::uint32_t) idex.branch_addr == (std::uint32_t) branch_addr_in);
    REQUIRE((std::uint32_t) idex.rs2d == (std::uint32_t) rs2d_in);

    switch(a_sel) {
       case 0:
            REQUIRE((std::uint32_t) idex.a == (std::uint32_t) rs1d);
            break;
        case 1:
            REQUIRE((std::uint32_t) idex.a == (std::uint32_t) pc_in);
            break;
        default:
            REQUIRE((std::uint32_t) idex.a == 0);
            break;
    }

    switch(b_sel) {
        case 0:
            REQUIRE((std::uint32_t) idex.b == (std::uint32_t) rs2d_in);
            break;
        case 1:
            REQUIRE((std::uint32_t) idex.b == (std::uint32_t) imm);
            break;
        case 2:
            REQUIRE((std::uint32_t) idex.b == 4);
            break;
        case 3:
            REQUIRE((std::uint32_t) idex.b == (std::uint32_t) imm << 12);
            break;
    }
}

static void init(auto& idex) {
    //Initialize Module
    idex.rstn = 1;
    idex.clk = 0;
    nyu::eval(idex);
    idex.rstn = 0;
    nyu::eval(idex);
} 

static void a_test(std::uint8_t a_sel) {
    auto& idex {nyu::getDUT<VIDEX>()};

    init(idex);

    // for (std::uint8_t b_sel {0}; b_sel < 4; ++b_sel)
    //     for (int branch_taken_in {0}; branch_taken_in < 2; ++branch_taken_in)
    //         for (std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
    //             for (std::uint32_t pc_in {0}; pc_in < 4; ++pc_in)
    //                 for (std::uint32_t imm {0}; imm < 4; ++imm)
    //                     for (std::uint32_t rs1d {0}; rs1d < 4; ++rs1d)
    //                         for (std::uint32_t rs2d_in {0}; rs2d_in < 4; ++rs2d_in)
    //                             for (std::uint32_t branch_addr_in {0}; branch_addr_in < 4; ++branch_addr_in)
    //                                 eval(idex, a_sel, b_sel, branch_taken_in, rdn_in, pc_in, imm, rs1d, rs2d_in, branch_addr_in);
    
    for (std::uint8_t b_sel {0}; b_sel < 4; ++b_sel)
        for (int branch_taken_in {0}; branch_taken_in < 2; ++branch_taken_in)
            for (std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
                for (std::uint32_t pc_in {1}; pc_in; pc_in <<= 1)
                    for (std::uint32_t imm {1}; imm; imm <<= 1)
                        for (std::uint32_t rs1d {1}; rs1d; rs1d <<= 1)
                            for (std::uint32_t rs2d_in {1}; rs2d_in; rs2d_in <<= 1)
                                for (std::uint32_t branch_addr_in {1}; branch_addr_in; branch_addr_in <<= 1)
                                    eval(idex, a_sel, b_sel, branch_taken_in, rdn_in, pc_in, imm, rs1d, rs2d_in, branch_addr_in);
}

static void b_test(std::uint8_t b_sel) {
    auto& idex {nyu::getDUT<VIDEX>()};

    init(idex);

    // for (std::uint8_t a_sel {0}; a_sel < 4; ++a_sel)
    //     for (int branch_taken_in {0}; branch_taken_in < 2; ++branch_taken_in)
    //         for (std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
    //             for (std::uint32_t pc_in {0}; pc_in < 4; ++pc_in)
    //                 for (std::uint32_t imm {0}; imm < 4; ++imm)
    //                     for (std::uint32_t rs1d {0}; rs1d < 4; ++rs1d)
    //                         for (std::uint32_t rs2d_in {0}; rs2d_in < 4; ++rs2d_in)
    //                             for (std::uint32_t branch_addr_in {0}; branch_addr_in < 4; ++branch_addr_in)
    //                                 eval(idex, a_sel, b_sel, branch_taken_in, rdn_in, pc_in, imm, rs1d, rs2d_in, branch_addr_in);
    
    for (std::uint8_t a_sel {0}; a_sel < 4; ++a_sel)
        for (int branch_taken_in {0}; branch_taken_in < 2; ++branch_taken_in)
            for (std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
                for (std::uint32_t pc_in {1}; pc_in; pc_in <<= 1)
                    for (std::uint32_t imm {1}; imm; imm <<= 1)
                        for (std::uint32_t rs1d {1}; rs1d; rs1d <<= 1)
                            for (std::uint32_t rs2d_in {1}; rs2d_in; rs2d_in <<= 1)
                                for (std::uint32_t branch_addr_in {1}; branch_addr_in; branch_addr_in <<= 1)
                                    eval(idex, a_sel, b_sel, branch_taken_in, rdn_in, pc_in, imm, rs1d, rs2d_in, branch_addr_in);
}

TEST_CASE("a_sel = 0") {
    a_test(0);
}   

TEST_CASE("a_sel = 1") {
    a_test(1);
}   

TEST_CASE("a_sel = 3") {
    a_test(3);
}   

TEST_CASE("b_sel = 0") {
    b_test(0);
}   

TEST_CASE("b_sel = 1") {
    b_test(1);
}    

TEST_CASE("b_sel = 2") {
    b_test(2);
}

TEST_CASE("b_sel = 3") {
    b_test(3);
}