#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VCon_ID.h>

static void eval(auto& con_id, bool wbe, bool addr_mode, bool branch_taken, std::uint8_t immode, 
std::uint8_t rdn_in, std::uint32_t ins, std::uint32_t pc_in, std::uint32_t rdd) {
    
    con_id.clk = 0;
    con_id.rstn = 1;
    nyu::eval(con_id);

    con_id.clk = 1;
    con_id.cache_clk = 0;
    con_id.rstn = 1;
    con_id.wbe = wbe;
    con_id.addr_mode = addr_mode;
    con_id.branch_taken = branch_taken;
    con_id.immode = immode;
    con_id.ins = ins;
    con_id.pc_in = pc_in;
    con_id.rdd = rdd;
    con_id.rdn_in = rdn_in;
    nyu::eval(con_id);

    con_id.cache_clk = 1;
    con_id.clk = 0;
    con_id.rstn = 1;
    con_id.wbe = wbe;
    con_id.addr_mode = addr_mode;
    con_id.branch_taken = branch_taken;
    con_id.immode = immode;
    con_id.ins = ins;
    con_id.pc_in = pc_in;
    con_id.rdd = rdd;
    con_id.rdn_in = rdn_in;
    nyu::eval(con_id);

    INFO("Testing wbe = " << wbe << ", addr_mode = " << addr_mode << ", branch_taken = " << branch_taken << ", immode = " << (int) immode << ", rdn_in = " << (int) rdn_in << ", ins = " << ins << ", pc_in = " << pc_in << ", and rdd = " << rdd);

    // Test pc passthrough
    REQUIRE((uint32_t) con_id.pc == (unit32_t) pc_in);

    switch(immode) {
        /* Note that the exact implementation of >> depends on the compiler. As such, this code is written with that in mind and as such the values 
        being checked against are calculated in such a way to ensure that >> can be treated logically or arithmetically and the result will be the same. */ 
        case 0:
            REQUIRE((std::uint32_t) con_id.imm == (std::uint32_t) 0);
            break;
        case 1:
            REQUIRE((std::uint32_t) con_id.imm == (std::uint32_t) (0xFFFFF000 * (bool) (ins & (1 << 31)) + ((ins & ((std::uint32_t)  (pow(2, 12) - 1) << 20)) >> 20)));
            break;
        case 2:
            REQUIRE((std::uint32_t) con_id.imm == (std::uint32_t) (0xFFFFF000 * (bool) (ins & (1 << 31)) + (((ins & ((std::uint32_t) (pow(2, 7) - 1) << 25)) >> 25 ) << 5 )+ ((ins & ((std::uint32_t) (pow(2, 5) - 1) << 7)) >> 7)));
            break;
        case 3:
            REQUIRE((std::uint32_t) con_id.imm == (std::uint32_t) (0xFFFFF000 * (bool) (ins & (1 << 31)) + (((ins & (1  << 7)) >> 7) << 11) + (((ins & ((std::uint32_t) (pow(2, 6) - 1) << 25)) >> 25) << 5) + (((ins & ((std::uint32_t) (pow(2, 4) - 1) << 8)) >> 8) << 1)));
            break;
        case 4:
            REQUIRE((std::uint32_t) con_id.imm == (std::uint32_t) (ins & 0xFFFFF000));
            break;
        case 5:
            REQUIRE((std::uint32_t) con_id.imm == (std::uint32_t) ((((ins & (1 << 31)) >> 11) + ((ins & ((std::uint32_t)  (pow(2, 8) - 1) << 12)))  +  ((ins & (1 << 20)) >> 9) + (((ins >> 20) & 0x7FE)) & 0x1FFFFF)));
            break;
        default:
            break;
    }

    if(addr_mode) {
        if (branch_taken) {
            REQUIRE((std::uint32_t) con_id.branch_addr == (std::uint32_t) (con_id.imm + con_id.rs1d));
            REQUIRE((std::uint32_t) con_id.npc == (std::uint32_t) con_id.branch_addr);
        }
        else {
            REQUIRE((std::uint32_t) con_id.branch_addr == (std::uint32_t) (con_id.imm + con_id.rs1d));
            REQUIRE((std::uint32_t) con_id.npc == (std::uint32_t) pc_in);
        }
    }

    else {
        if (branch_taken) {
            REQUIRE((std::uint32_t) con_id.branch_addr == (std::uint32_t) (pc_in + model.imm));
            REQUIRE((std::uint32_t) con_id.npc == (std::uint32_t) con_id.branch_addr);
        }
        else {
            REQUIRE((std::uint32_t) con_id.branch_addr == (std::uint32_t) (pc_in + con_id.imm));
            REQUIRE((std::uint32_t) con_id.npc == (std::uint32_t) pc_in);
        }
    }
}

static void eval_regs(auto& con_id, bool wbe, bool addr_mode, bool branch_taken, std::uint8_t immode, 
std::uint8_t rdn_in, std::uint32_t ins, std::uint32_t pc_in, std::uint32_t rdd, uint32_t &regvals[32]) {

    //Calculate RS1N and RS2N
    std::uint8_t rs1n = (std::uint8_t) ((ins & (31 << 15)) >> 15);
    std::uint8_t rs2n = (std::uint8_t) ((ins & (31 << 20)) >> 20);

    //Simulate register behavior
    if (wbe && rdn_in) regvals[rdn_in] = (uint32_t) rdd;

    con_id.clk = 0;
    con_id.rstn = 1;
    nyu::eval(con_id);

    con_id.clk = 1;
    con_id.cache_clk = 0;
    con_id.rstn = 1;
    con_id.wbe = wbe;
    con_id.addr_mode = addr_mode;
    con_id.branch_taken = branch_taken;
    con_id.immode = immode;
    con_id.ins = ins;
    con_id.pc_in = pc_in;
    con_id.rdd = rdd;
    con_id.rdn_in = rdn_in;
    nyu::eval(con_id);

    con_id.cache_clk = 1;
    con_id.clk = 0;
    con_id.rstn = 1;
    con_id.wbe = wbe;
    con_id.addr_mode = addr_mode;
    con_id.branch_taken = branch_taken;
    con_id.immode = immode;
    con_id.ins = ins;
    con_id.pc_in = pc_in;
    con_id.rdd = rdd;
    con_id.rdn_in = rdn_in;
    nyu::eval(con_id);

    INFO("Testing rs1n = " << (int) rs1n << ", rs2n = " << (int) rs2n << ", wbe = " << wbe << ", addr_mode = " << addr_mode << ", branch_taken = " << branch_taken << ", immode = " << (int) immode << ", rdn_in = " << (int) rdn_in << ", ins = " << ins << ", pc_in = " << pc_in << ", and rdd = " << rdd);

    // Test pc passthrough
    REQUIRE((uint32_t) con_id.pc == (unit32_t) pc_in);

    //Test register data output
    REQUIRE((std::uint32_t) con_id.rs1d == (std::uint32_t) regvals[rs1n]);
    REQUIRE((std::uint32_t) con_id.rs2d == (std::uint32_t) regvals[rs2n]);
}

static void init(auto& con_id) {
    //Initialize Module
    con_id.rstn = 1;
    con_id.clk = 0;
    con_id.cache_clk = 0;
    nyu::eval(con_id);
    con_id.clk = 0;
    con_id.cache_clk = 0;
    con_id.rstn = 0;
    nyu::eval(con_id);
}

static void test_imm(std::uint8_t immode) {
    auto& con_id {nyu::getDUT<VCON_ID>()};

    init(con_id);

    for (int wbe {0}; wbe < 2; ++wbe)
        for (int addr_mode {0}; addr_mode < 2; ++addr_mode) 
            for (int branch_taken {0}; branch_taken < 2; ++branch_taken) 
                for (std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in) 
                    for (std::uint32_t ins {0}; ins < 32; ++ins)
                        for (std::uint32_t pc_in {0}; pc_in < 32; ++pc_in) 
                            for(std::uint32_t rdd {0}; rdd < 32; ++rdd)
                                eval(con_id, wbe, addr_mode, branch_taken, immode, rdn_in, ins, pc_in, rdd);

    for (int wbe {0}; wbe < 2; ++wbe)
        for (int addr_mode {0}; addr_mode < 2; ++addr_mode) 
            for (int branch_taken {0}; branch_taken < 2; ++branch_taken) 
                for (std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1) 
                    for (std::uint32_t ins {1}; ins; ins <<= 1)
                        for (std::uint32_t pc_in {1}; pc_in; pc_in <<= 1) 
                            for(std::uint32_t rdd {1}; rdd; rdd <<= 1)
                                eval(con_id, wbe, addr_mode, branch_taken, immode, rdn_in, ins, pc_in, rdd);

}



static void test_branch(bool addr_mode, bool branch_taken) {
    auto& con_id {nyu::getDUT<VCON_ID>()};

    init(con_id);
    

    for (int wbe {0}; wbe < 2; ++wbe)
       for (std::uint8_t immode {0}; immode < 6; ++immode) 
            for (std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in) 
                for (std::uint32_t ins {0}; ins < 32; ++ins)
                    for (std::uint32_t pc_in {0}; pc_in < 32; ++pc_in) 
                        for(std::uint32_t rdd {0}; rdd < 32; ++rdd)
                            eval(con_id, wbe, addr_mode, branch_taken, immode, rdn_in, ins, pc_in, rdd);
                            

     for (int wbe {0}; wbe < 2; ++wbe)
       for (std::uint8_t immode {0}; immode < 6; ++immode) 
            for (std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1) 
                for (std::uint32_t ins {1}; ins; ins <<= 1)
                    for (std::uint32_t pc_in {1}; pc_in; pc_in <<= 1) 
                        for(std::uint32_t rdd {1}; rdd; rdd <<= 1)
                            eval(con_id, wbe, addr_mode, branch_taken, immode, rdn_in, ins, pc_in, rdd);
}

static void test_regs() {

    auto& con_id {nyu::getDUT<VCON_ID>()};

    init(con_id);
    
    uint32_t regvals[32] = {0};

     for (int wbe {0}; wbe < 2; ++wbe)
        for (int addr_mode {0}; addr_mode < 2; ++addr_mode) 
            for (int branch_taken {0}; branch_taken < 2; ++branch_taken) 
                for (std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in) 
                    for (std::uint32_t ins {0}; ins < 32; ++ins)
                        for (std::uint32_t pc_in {0}; pc_in < 32; ++pc_in) 
                            for(std::uint32_t rdd {0}; rdd < 32; ++rdd)
                                for (std::uint8_t immode {0}; immode < 6; ++immode) 
                                    eval_regs(con_id, wbe, addr_mode, branch_taken, immode, rdn_in, ins, pc_in, rdd, regvals);

        for (int wbe {0}; wbe < 2; ++wbe)
            for (int addr_mode {0}; addr_mode < 2; ++addr_mode) 
                for (int branch_taken {0}; branch_taken < 2; ++branch_taken) 
                    for (std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1) 
                        for (std::uint32_t ins {1}; ins; ins <<= 1)
                            for (std::uint32_t pc_in {1}; pc_in; pc_in <<= 1) 
                                for(std::uint32_t rdd {1}; rdd; rdd <<= 1)
                                    for (std::uint8_t immode {0}; immode < 6; ++immode) 
                                        eval_regs(con_id, wbe, addr_mode, branch_taken, immode, rdn_in, ins, pc_in, rdd, regvals);
}

TEST_CASE("Con_ID, Imm Mode 0") {
    test_imm(0);
}

TEST_CASE("Con_ID, Imm Mode 1") {
    test_imm(1);
}

TEST_CASE("Con_ID, Imm Mode 2") {
    test_imm(2);
}

TEST_CASE("Con_ID, Imm Mode 3") {
    test_imm(3);
}

TEST_CASE("Con_ID, Imm Mode 4") {
    test_imm(4);
}

TEST_CASE("Con_ID, Imm Mode 5") {
    test_imm(5);
}

TEST_CASE("Con_ID, PC No Branch") {  //Case when branch_addr = pc + imm, but branch is not taken
    test_branch(0, 0);
}

TEST_CASE("Con_ID, PC Branch") {  //Case when branch_addr = pc + imm, and branch is taken
    test_branch(0, 1);
}

TEST_CASE("Con_ID, RS1D No Branch") {  //Case when branch_addr = imm + rs1d, but branch is not taken
    test_branch(1, 0);
}

TEST_CASE("Con_ID, RS1D Branch") {  //Case when branch_addr = rs1d, and branch is taken
    test_branch(1, 1);
}

TEST_CASE("Con_ID, REGS") {
    test_regs();
}