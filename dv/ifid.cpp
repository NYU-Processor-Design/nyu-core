#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VIFID.h>

static void eval(auto& ifid, std::uint8_t immode, std::uint32_t pc_in, std::int32_t ins_in) {
    ifid.clk = 0;
    ifid.rstn = 1;
    nyu::eval(ifid);

    ifid.clk = 1;
    ifid.rstn = 1;
    ifid.immode = immode;
    ifid.pc_in = pc_in;
    ifid.ins = ins_in;
    nyu::eval(ifid);

    INFO("Testing immode = " << (std::uint32_t) immode << ", pc_in = " << (std::uint32_t) pc_in << ", and ins_in = " << (std::uint32_t) ins_in);

    // Test pc passthrough
    REQUIRE((std::uint32_t) ifid.pc == (std::uint32_t) pc_in);

    //Test Deciphering of Register Numbers
    REQUIRE((std::uint8_t) ifid.rdn == (std::uint8_t) ((ins_in & (31 << 7)) >> 7));
    REQUIRE((std::uint8_t) ifid.rs1n == (std::uint8_t) ((ins_in & (31 << 15)) >> 15));
    REQUIRE((std::uint8_t) ifid.rs2n == (std::uint8_t) ((ins_in & (31 << 20)) >> 20));

    switch(immode) {
        /* Note that the exact implementation of >> depends on the compiler. As such, this code is written with that in mind and as such the values 
        being checked against are calculated in such a way to ensure that >> can be treated logically or arithmetically and the result will be the same. */ 
        case 0:
            REQUIRE((std::uint32_t) ifid.imm == (std::uint32_t) 0);
            break;
        case 1:
            REQUIRE((std::uint32_t) ifid.imm == (std::uint32_t) (0xFFFFF000 * (bool) (ins_in & (1 << 31)) + ((ins_in & ((std::uint32_t)  (pow(2, 12) - 1) << 20)) >> 20)));
            break;
        case 2:
            REQUIRE((std::uint32_t) ifid.imm == (std::uint32_t) (0xFFFFF000 * (bool) (ins_in & (1 << 31)) + (((ins_in & ((std::uint32_t) (pow(2, 7) - 1) << 25)) >> 25 ) << 5 )+ ((ins_in & ((std::uint32_t) (pow(2, 5) - 1) << 7)) >> 7)));
            break;
        case 3:
            REQUIRE((std::uint32_t) ifid.imm == (std::uint32_t) (0xFFFFF000 * (bool) (ins_in & (1 << 31)) + (((ins_in & (1  << 7)) >> 7) << 11) + (((ins_in & ((std::uint32_t) (pow(2, 6) - 1) << 25)) >> 25) << 5) + (((ins_in & ((std::uint32_t) (pow(2, 4) - 1) << 8)) >> 8) << 1)));
            break;
        case 4:
            REQUIRE((std::uint32_t) ifid.imm == (std::uint32_t) (ins_in & 0xFFFFF000));
            break;
        case 5:
            REQUIRE((std::uint32_t) ifid.imm == (std::uint32_t) ((((ins_in & (1 << 31)) >> 11) + ((ins_in & ((std::uint32_t)  (pow(2, 8) - 1) << 12)))  +  ((ins_in & (1 << 20)) >> 9) + (((ins_in >> 20) & 0x7FE)) & 0x1FFFFF)));
            break;
        default:
            break;
    }

}

static void init(auto& ifid) {
    ifid.rstn = 1;
    ifid.clk = 0;
    nyu::eval(ifid);
    ifid.rstn = 0;
    nyu::eval(ifid);
}

static void test(std::uint8_t immode) {
    auto& ifid {nyu::getDUT<VIFID>()};

    init(ifid);

    for(std::uint32_t pc_in {0}; pc_in < 512; ++pc_in)
        for(std::uint32_t ins_in {0}; ins_in < 512; ++ins_in)
            eval(ifid, immode, pc_in, ins_in);

    for(std::uint32_t pc_in {1}; pc_in; pc_in <<= 1)
        for(std::uint32_t ins_in {1}; ins_in; ins_in <<= 1)
            eval(ifid, immode, pc_in, ins_in);

}

TEST_CASE("IFID, Imm Mode 0") {
    test(0);
}

TEST_CASE("IFID, Imm Mode 1") {
    test(1);
}

TEST_CASE("IFID, Imm Mode 2") {
    test(2);
}

TEST_CASE("IFID, Imm Mode 3") {
    test(3);
}

TEST_CASE("IFID, Imm Mode 4") {
    test(4);
}

TEST_CASE("IFID, Imm Mode 5") {
    test(5);
}
