#include <catch2/catch_test_macros.hpp>
#include <VIFID.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

VIFID model;
bool clk;
bool rstn;
uint8_t immode;
uint32_t pc_in;
uint32_t ins_in;


TEST_CASE("PC Passthrough") {
    VIFID model;
    bool clk;
    bool rstn;
    uint8_t immode;
    uint32_t pc_in;
    uint32_t ins_in;

    for (int i = 0; i < 1000; i++) {
        ins_in = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        immode = rand() % (int) (7);
        
        //Initalize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test PC Passthrough
        model.clk = 1;
        model.immode = immode;
        model.pc_in = pc_in;
        model.ins_in = ins_in;
        model.eval();
        REQUIRE((uint32_t) model.pc == (uint32_t) pc_in);
    }
}   

TEST_CASE("Decypher Register Numbers") {
    VIFID model;
    bool clk;
    bool rstn;
    uint8_t immode;
    uint32_t pc_in;
    uint32_t ins_in;

    for (int i = 0; i < 1000; i++) {
        ins_in = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        immode = rand() % (int) (7);
        
        //Initalize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test PC Passthrough
        model.clk = 1;
        model.immode = immode;
        model.pc_in = pc_in;
        model.ins_in = ins_in;
        model.eval();
        REQUIRE((uint8_t) model.rdn == (uint8_t) ((ins_in & (31 << 7)) >> 7))
        REQUIRE((uint8_t)model.rs1n == (uint8_t) ((ins_in & (31 << 15)) >> 15))
        REQUIRE((uint8_t) model.rdn == (uint8_t) ((ins_in & (31 << 20)) >> 20))
    }
}

TEST_CASE("Imm Mode 0") {

    VIFID model;
    bool clk;
    bool rstn;
    uint8_t immode;
    uint32_t pc_in;
    uint32_t ins_in;

    for (int i = 0; i < 1000; i++) {
        ins_in = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        immode = 0;
        
        //Initalize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 0
        model.clk = 1;
        model.immode = immode;
        model.pc_in = pc_in;
        model.ins_in = ins_in;
        model.eval();

        REQUIRE((uint32_t) model.imm == (uint32_t) 0)
    }

}

TEST_CASE("Imm Mode 1") {

    VIFID model;
    bool clk;
    bool rstn;
    uint8_t immode;
    uint32_t pc_in;
    uint32_t ins_in;

    for (int i = 0; i < 1000; i++) {
        ins_in = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        immode = 1;
        
        //Initalize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 1
        model.clk = 1;
        model.immode = immode;
        model.pc_in = pc_in;
        model.ins_in = ins_in;
        model.eval();
        REQUIRE((uint32_t) model.imm == (uint32_t) {{(20){((ins_in & (1 << 31))>> 31)}}, (ins_in & ((pow(2, 12) - 1) << 20)) >> 20})
    }

}

TEST_CASE("Imm Mode 2") {

    VIFID model;
    bool clk;
    bool rstn;
    uint8_t immode;
    uint32_t pc_in;
    uint32_t ins_in;

    for (int i = 0; i < 1000; i++) {
        ins_in = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        immode = 1;
        
        //Initalize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 1
        model.clk = 1;
        model.immode = immode;
        model.pc_in = pc_in;
        model.ins_in = ins_in;
        model.eval();
        REQUIRE((uint32_t) model.imm == (uint32_t) {{(20){((ins_in & (1 << 31))>> 31)}}, (ins_in & ((pow(2, 7) - 1) << 25)) >> 25, (ins_in & ((pow(2, 5) - 1) << 7)) >> 7})
    }
}

TEST_CASE("Imm Mode 3") {
    
    VIFID model;
    bool clk;
    bool rstn;
    uint8_t immode;
    uint32_t pc_in;
    uint32_t ins_in;

    for (int i = 0; i < 1000; i++) {
        ins_in = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        immode = 1;
        
        //Initalize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 1
        model.clk = 1;
        model.immode = immode;
        model.pc_in = pc_in;
        model.ins_in = ins_in;
        model.eval();
        REQUIRE((uint32_t) model.imm == (uint32_t) {{(20){((ins_in & (1 << 31))>> 31)}}, (ins_in & ((pow(2, 7) - 1) << 25)) >> 25, (ins_in & ((pow(2, 5) - 1) << 7)) >> 7})
    }

}

TEST_CASE("Imm Mode 4") {

}

TEST_CASE("Imm Mode 5") {

}

TEST_CASE("Imm Mode 6") {

}