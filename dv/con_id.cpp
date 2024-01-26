#include <catch2/catch_test_macros.hpp>
#include <VCon_ID.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

TEST_CASE("Con_ID PC Passthrough") {
    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test Passthrough
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.pc == (unit32_t) pc_in);
    }
}

TEST_CASE("Con_ID Decipher Register Numbers") {
    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test Deciphering Register Numbers
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint8_t) model.rdn == (uint8_t) ((ins & (31 << 7)) >> 7));
        REQUIRE((uint8_t) model.rs1n == (uint8_t) ((ins & (31 << 15)) >> 15));
        REQUIRE((uint8_t) model.rs2n == (uint8_t) ((ins & (31 << 20)) >> 20));
    }
}

TEST_CASE("Con_ID Imm Mode 0") {

    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = 0;
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 0
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.imm == (uint32_t) 0);
    }

}

TEST_CASE("Con_ID Imm Mode 1") {

    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = 1;
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 1
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

         REQUIRE((uint32_t) model.imm == (uint32_t) ((((uint32_t)  (pow(2, 20) - 1) & ((ins & (1 << 31))>> 31)) << 31) + ((ins & ((uint32_t)  (pow(2, 12) - 1) << 20)) >> 20)));
    }
}

TEST_CASE("Con_ID Imm Mode 2") {

    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = 2;
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 2
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.imm == (uint32_t) ((((uint32_t) (pow(2, 20) - 1) & ((ins & (1 << 31))>> 31)) << 31) + (((ins & ((uint32_t) (pow(2, 7) - 1) << 25)) >> 25 ) << 5 )+ ((ins & ((uint32_t) (pow(2, 5) - 1) << 7)) >> 7)));
    }

}

TEST_CASE("Con_ID Imm Mode 3") {

    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = 3;
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 3
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

         REQUIRE((uint32_t) model.imm == (uint32_t) ((((uint32_t) (pow(2, 19) - 1) & ((ins & (1 << 31))>> 31)) << 31) + (((ins & (1 << 31)) >> 31) << 12) + (((ins & (1  << 7)) >> 7) << 11) + (((ins & ((uint32_t) (pow(2, 6) - 1) << 25)) >> 25) << 5) + (((ins & ((uint32_t) (pow(2, 4) - 1) << 8)) >> 8) << 1)));
    }

}

TEST_CASE("Con_ID Imm Mode 4") {

    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = 4;
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 4
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.imm == (uint32_t) ((((ins & ((uint32_t) (pow(2, 20) - 1) << 12)) >> 12) << 12)));
    }
}

TEST_CASE("Con_ID Imm Mode 5") {

    VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = rand() % (int) (pow(2, 1));
        branch_taken = rand() % (int) (pow(2, 1));
        immode = 5;
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test IMM Mode 5
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

       REQUIRE((uint32_t) model.imm == (uint32_t) ((( (ins & (1 << 31)) >> 31) << 20) + ((ins & ((uint32_t)  (pow(2, 8) - 1) << 12)))  +  (((ins & (1 << 20)) >> 20) << 11) + (((ins & ((uint32_t)  (pow(2, 11) - 1) << 21)) >> 21) << 1)));
    }
}

TEST_CASE("Con_ID PC No Branch") {  //Case when branch_addr = pc + imm, but branch is not taken
   VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = 0;
        branch_taken = 0;
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (pc_in + model.imm));
        REQUIRE((uint32_t) model.npc == (uint32_t) pc_in);
    }


}

TEST_CASE("Con_ID PC Branch") {  //Case when branch_addr = pc + imm, and branch is taken
   VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = 0;
        branch_taken = 1;
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (pc_in + model.imm));
        REQUIRE((uint32_t) model.npc == (uint32_t) branch_addr);
    }

}

TEST_CASE("Con_ID RS1D No Branch") {  //Case when branch_addr = imm + rs1d, but branch is not taken
   VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

    //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = 1;
        branch_taken = 0;
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        

        //Test
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (model.imm + model.rs1d));
        REQUIRE((uint32_t) model.npc == (uint32_t) pc_in);
    }
}

TEST_CASE("Con_ID RS1D Branch") {  //Case when branch_addr = rs1d, and branch is taken
   VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;

     //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = 1;
        branch_taken = 1;
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));

        //Test
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (model.imm + model.rs1d));
        REQUIRE((uint32_t) model.npc == (uint32_t) model.branch_addr);
    }
}

TEST_CASE("Con_ID REGS") { 
   VCon_ID model;
    bool clk;
    bool cache_clk;
    bool rstn;
    bool wbe;
    bool addr_mode;
    bool branch_taken;
    uint8_t immode;
    uint8_t rdn_in;
    uint32_t ins;
    uint32_t pc_in;
    uint32_t rdd;
    uint8_t rdn_in;
    uint32_t regvals[32] = {0};
    uint8_t rs1n;
    uint8_t rs2n;

     //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.cache_clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

    for (int i = 0; i < 1000; i++) {
        wbe = rand() % (int) (pow(2, 1));
        addr_mode = 1;
        branch_taken = 1;
        immode = rand() % (int) (pow(2, 3));
        ins =  rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdd = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));

        //Calculate RS1N and RS2N
        rs1n = (uint8_t) ((ins_in & (31 << 15)) >> 15);
        rs2n = (uint8_t) ((ins_in & (31 << 20)) >> 20);

        //Simulate register behavior
        if (wbe && rdn_in) regvals[rdn_in] = (uint32_t) rdd;

        //Test
        model.clk = 1;
        model.cache_clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();

        model.cache_clk = 1;
        model.clk = 0;
        model.rstn = 1;
        model.wbe = wbe;
        model.addr_mode = addr_mode;
        model.branch_taken = branch_taken;
        model.immode = immode;
        model.ins = ins;
        model.pc_in = pc_in;
        model.rdd = rdd;
        model.rdn_in = rdn_in;
        model.eval();
        
        REQUIRE((uint32_t) model.rs1d == (uint32_t) regvals[rs1n]);
        REQUIRE((uint32_t) model.rs2d == (uint32_t) regvals[rs2n]);
    }
}