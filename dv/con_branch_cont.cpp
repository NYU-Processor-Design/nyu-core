#include <catch2/catch_test_macros.hpp>
#include <VCon_Branch_Cont.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

TEST_CASE("Value Passthrough Con con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;

    for(int i=0;i<1000;i++){
        rstn_h=rand() % (int) (pow(2, 1));
        pred_taken=rand() % (int) (pow(2, 1));
        branch_occr=rand() % (int) (pow(2, 2));
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));

         //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.rstn_h=rstn_h;
        model.pred_taken=pred_taken;
        model.branch_occr=branch_occr;
        model.branch_cond=branch_cond;
        model.pred_pc=pred_pc;
        model.pred_addr=pred_addr;
        model.alu_out=alu_out;
        model.npc_in=npc_in;
        model.eval();
        REQUIRE((uint32_t) model.npc == (uint32_t) npc_in);
    }
}

TEST_CASE("Branch Prediction Correct con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;

        rstn_h=1;
        pred_taken=1;
        branch_occr=1;
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));

         //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.rstn_h=rstn_h;
        model.pred_taken=pred_taken;
        model.branch_occr=branch_occr;
        model.branch_cond=branch_cond;
        model.pred_pc=pred_pc;
        model.pred_addr=pred_addr;
        model.alu_out=alu_out;
        model.npc_in=npc_in;
        model.eval();
        REQUIRE((bool) model.branch_taken == 1);
    
}

TEST_CASE("Branch Prediction Incorrect con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;

        rstn_h=1;
        pred_taken=0;
        branch_occr=1;
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));

         //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        //Test Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.rstn_h=rstn_h;
        model.pred_taken=pred_taken;
        model.branch_occr=branch_occr;
        model.branch_cond=branch_cond;
        model.pred_pc=pred_pc;
        model.pred_addr=pred_addr;
        model.alu_out=alu_out;
        model.npc_in=npc_in;
        model.eval();
        REQUIRE((bool) model.branch_taken == 1);
    
}


