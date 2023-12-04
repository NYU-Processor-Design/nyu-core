#include <catch2/catch_test_macros.hpp>
#include <VCon_EX.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>


TEST_CASE("Value Passthrough") {
    
    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = rand() % (int) (pow(2, 8));
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((bool) model.branch_taken == (bool) branch_taken_in);
        REQUIRE((uint32_t) model.pc == (uint32_t) pc_in);
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) branch_addr_in);
        REQUIRE((uint8_t) model.rdn == (uint8_t) rdn_in);
        REQUIRE((uint32_t) model.rs2d == (uint32_t) rs2d_in);
    }
}   

uint32_t calc_a (uint8_t a_sel, uint32_t rs1d, uint32_t pc_in) {
    if (a_sel == 0) return rs1d;
    else if (a_sel == 1) return pc_in;
    else return 0;
}

uint32_t calc_b (uint8_t b_sel, uint32_t rs2d, uint32_t imm) {
    if (b_sel == 0) return rs2d;
    else if (b_sel == 1) return imm;
    else if (b_sel == 2) return 4;
    else return imm << 12;
}


TEST_CASE("ADD") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x0;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test ADD
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE( (uint32_t) model.alu_out == (uint32_t) (a + b));
    }   
}

TEST_CASE("SUB") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x20;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test SUB
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (a + (~b + 1)));
    }  
}

TEST_CASE("XOR") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test XOR
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (a ^ b));
    }  
}

TEST_CASE("OR") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x06;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test OR
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE( (uint32_t) model.alu_out == (uint32_t) (a | b));
    }  
}

TEST_CASE("AND") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test AND
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (a & b));
    }  
}

TEST_CASE("LLS") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test LLS
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (a << (b & 31)));
    }  
}

TEST_CASE("LRS") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test LRS
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (a >> (b & 31)));

    }

}

TEST_CASE("ARS") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;
    uint32_t expected;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        if (a >> 31) {
            expected = (a >> (b & 31));
            for (int i = 32 - (b & 31); i < 32; i++) {
                expected += 1 << i;
            }
        }
        else {
        expected = (a >> (b & 31));
        }

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test ARS
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == expected);
    }

}

TEST_CASE("SSLT") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test SSLT
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (((a & (1 << 31)) & ~(b & (1 << 31)))? 1 : (~(a & (1 << 31)) & (b & (1 << 31))) ? 0 : a < b));

    }

}

TEST_CASE("USLT") {

    VCon_EX model;
    uint8_t a_sel;
    uint8_t b_sel;
    bool branch_taken_in;
    uint32_t imm;
    uint32_t pc_in;
    uint8_t rdn_in;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;
    uint8_t alu_mode;

    uint32_t a;
    uint32_t b;

    for (int i = 0; i < 1000; i++) {
        a_sel = rand() % (int) (pow(2, 2));
        b_sel = rand() % (int) (pow(2, 2));
        branch_taken_in  = rand() % (int) (pow(2, 1));
        imm = rand() % (int) (pow(2, 32));
        pc_in = rand() % (int) (pow(2, 32));
        rdn_in = rand() % (int) (pow(2, 5));
        rs1d = rand() % (int) (pow(2, 32));
        rs2d_in = rand() % (int) (pow(2, 32));
        branch_addr_in = rand() % (int) (pow(2, 32));
        alu_mode = 0x04;
        
        a = calc_a(a_sel, rs1d, pc_in);
        b = calc_b(b_sel, rs2d_in, imm);

        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test LRS
        model.clk = 1;
        model.rstn = 1;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.branch_taken_in = branch_taken_in;
        model.imm = imm;
        model.pc_in = pc_in;
        model.rdn_in = rdn_in;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.alu_mode = alu_mode;
        model.eval();
        REQUIRE((uint32_t) model.alu_out == (uint32_t) (a < b));
    }
}

