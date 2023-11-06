#include <catch2/catch_test_macros.hpp>
#include <VIDEX.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>


TEST_CASE("Value Passthroughs") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = rand() % (int) (pow(2, 2) - 1);
        b_sel = rand() % (int) (pow(2, 2) - 1);
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.pc == (uint32_t) pc_in);
        REQUIRE((uint8_t) model.rdn == (uint8_t) rdn_in);
        REQUIRE((bool) model.branch_taken == (bool) branch_taken_in);
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) branch_addr_in);
    }
}   

TEST_CASE("a_sel = 0") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = 0;
        b_sel = rand() % (int) (pow(2, 2) - 1);
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test a = rs1d
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.a == (uint32_t) rs1d);
    }
}   

TEST_CASE("a_sel = 1") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = 1;
        b_sel = rand() % (int) (pow(2, 2) - 1);
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test a = pc_in
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.a == (uint32_t) pc_in);
    }
}   

TEST_CASE("a_sel = 3") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = 3;
        b_sel = rand() % (int) (pow(2, 2) - 1);
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test a = 0
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.a == (uint32_t) 0);
    }
}   

TEST_CASE("b_sel = 0") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = rand() % (int) (pow(2, 2) - 1);
        b_sel = 0;
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test b = rs2d_in
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.b == (uint32_t) rs2d_in);
    }
}   

TEST_CASE("b_sel = 1") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = rand() % (int) (pow(2, 2) - 1);
        b_sel = 1;
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test b = imm
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.b == (uint32_t) imm);
    }
}    

TEST_CASE("b_sel = 2") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = rand() % (int) (pow(2, 2) - 1);
        b_sel = 2;
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test b = 4
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.b == (uint32_t) 4);
    }
}   

TEST_CASE("b_sel = 3") {
    
    VIDEX model;
    bool branch_taken_in;
    uint8_t a_sel;
    uint8_t b_sel;
    uint8_t rdn_in;
    uint32_t pc_in;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t rs2d_in;
    uint32_t branch_addr_in;

    for (int i = 0; i < 1000; i++) {
        branch_taken_in  = rand() % (int) (pow(2, 1) - 1);
        a_sel = rand() % (int) (pow(2, 2) - 1);
        b_sel = 3;
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        imm = rand() % (int) (pow(2, 32) - 1);
        pc_in = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        rs2d_in = rand() % (int) (pow(2, 32) - 1);
        branch_addr_in = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test b = imm << 12
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken_in = branch_taken_in;
        model.a_sel = a_sel;
        model.b_sel = b_sel;
        model.rdn_in = rdn_in;
        model.pc_in = pc_in;
        model.imm = imm;
        model.rs1d = rs1d;
        model.rs2d_in = rs2d_in;
        model.branch_addr_in = branch_addr_in;
        model.eval();
        REQUIRE((uint32_t) model.b == (uint32_t) imm << 12);
    }
}   