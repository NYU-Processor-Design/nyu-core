#include <catch2/catch_test_macros.hpp>
#include <VCon_Branch_Cont.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

TEST_CASE("con_branch_cont reset"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;
    uint8_t rstn_out;
    bool branch_taken;

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

        REQUIRE((uint32_t) model.npc == 0);
        REQUIRE((bool) model.branch_taken == 0);
        REQUIRE((uint8_t) model.rstn_out == 0);


        //Test Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.rstn_h=0;
        model.pred_taken=pred_taken;
        model.branch_occr=branch_occr;
        model.branch_cond=branch_cond;
        model.pred_pc=pred_pc;
        model.pred_addr=pred_addr;
        model.alu_out=alu_out;
        model.npc_in=npc_in;
        model.eval();

        REQUIRE((uint32_t) model.npc == 0);
        REQUIRE((bool) model.branch_taken == 0);
        REQUIRE((uint8_t) model.rstn_out == 0);
    }
}

TEST_CASE("Branch Prediction & Occr con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;
    uint8_t rstn_out;
    bool branch_taken;

        rstn_h=1;
        pred_taken=1;
        branch_occr=0b11;
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
        REQUIRE((uint32_t) model.npc == (uint32_t)pred_addr);
    
}

TEST_CASE("No Branch Prediction  & Not Occr con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;
    uint8_t rstn_out;
    bool branch_taken;

        rstn_h=1;
        pred_taken=0;
        branch_occr=0b00;
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
        REQUIRE((uint32_t) model.npc == (uint32_t)npc_in);
        REQUIRE((bool) model.branch_taken == 0);
    
}


TEST_CASE(" No Branch Prediction &  Occr con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;
    uint8_t rstn_out;
    bool branch_taken;

        rstn_h=1;
        pred_taken=0;
        branch_occr=0b01;
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
        REQUIRE((uint32_t) model.npc == (uint32_t)pred_addr);
        REQUIRE((bool) model.branch_taken == 1);
}


TEST_CASE("Branch Prediction  &  Not Occr con_branch_cont"){
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;
    uint8_t rstn_out;
    bool branch_taken;

        rstn_h=1;
        pred_taken=1;
        branch_occr=0b01;
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
        REQUIRE((uint32_t) model.npc == (uint32_t)(pred_pc+4));
        REQUIRE((bool) model.branch_taken == 0);
}