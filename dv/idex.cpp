#include <catch2/catch_test_macros.hpp>
#include <VIDEX.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>


TEST_CASE("Value Passthroughs") {
    
    VIFID model;
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
        branch_taken  = rand() % (int) (pow(2, 1) - 1);
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

        
        //Test PC Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.branch_taken = branch_taken;
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
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) branch_addrin);
    }
}   