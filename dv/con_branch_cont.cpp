#include <catch2/catch_test_macros.hpp>
#include <VCon_Branch_Cont.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>
#include <iostream>
bool eval_act(uint32_t alu_out, uint8_t cond) {
    bool act;
    switch(cond){
        case 0:
        act=0;
        break;
        case 1:
        act=(bool)alu_out;
        break;
        case 2:
        act=~(bool) alu_out;
        break;
        case 3:
        act=1;
        break;
    }
    return act;

    
}

TEST_CASE("Con_Branch_Cont Non Prediction Instruction") { 
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
    bool act_taken;
    for(int i =0;i<1000;i++){
        rstn_h=rand() % (int) (pow(2, 1));
        pred_taken=rand() % (int) (pow(2, 1));
        branch_occr=rand() % (int) (pow(2, 1));
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));
        act_taken=eval_act( alu_out,  branch_cond);
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
        
        REQUIRE ((bool) model.branch_taken == (bool) branch_occr); 
    }
}

TEST_CASE("Con_Branch_Cont Prediction Instruction") { 
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
    bool act_taken;
        //Initialize Register Tracker Variables
    bool curr_pred = 0;
    bool incorrect_pred = 0;

    for(int i =0;i<1000;i++){
        rstn_h=rand() % (int) (pow(2, 1));
        pred_taken=rand() % (int) (pow(2, 1));
        branch_occr=2+rand() % (int) (pow(2, 1));
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));
        act_taken=eval_act( alu_out, branch_cond);
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

        if (__builtin_parity(branch_cond) == 0) {
            break;
        }
        else if ((act_taken ^ pred_taken) == 0) {
            incorrect_pred = 0;
        }
        else if (incorrect_pred == 1) {
            curr_pred = ~curr_pred;
            incorrect_pred = 1;
        }
        else {
            incorrect_pred = 1;
        }

        model.eval();
        
        REQUIRE ((bool) model.branch_taken == (bool) curr_pred);
    }
}

TEST_CASE("Con_Branch_Cont flush == 0 & Correct Prediction") { 
    VCon_Branch_Cont model;
    bool rstn_h;
    bool pred_taken;
    bool act_taken;
    uint8_t branch_occr;
    uint8_t branch_cond;
    uint32_t pred_pc;
    uint32_t pred_addr;
    uint32_t alu_out;
    uint32_t npc_in;
    uint8_t rstn_out;
    bool branch_taken;

    uint32_t npc_corr;
    for(int i =0;i<1000;i++){
        rstn_h=1;
        pred_taken=rand() % (int) (pow(2, 1));
        branch_occr=rand() % (int) (pow(2, 1));
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));
        act_taken=eval_act( alu_out, branch_cond);
         //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();
        if(pred_taken==act_taken){
            
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
        REQUIRE(model.rstn_out == 0); //Verilator translates High Z outputs to 0
        } 
    }
}

TEST_CASE("Con_Branch_Cont flush == 1 & Incorrect Prediction ") { 
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
    bool act_taken;
    uint32_t npc_corr;
    for(int i =0;i<1000;i++){
        rstn_h=1;
        pred_taken=rand() % (int) (pow(2, 1));
        branch_occr=rand() % (int) (pow(2, 1));
        branch_cond=rand() % (int) (pow(2, 2));
        pred_pc=rand() % (int) (pow(2, 32));
        pred_addr=rand() % (int) (pow(2, 32));
        alu_out=rand() % (int) (pow(2, 32));
        npc_in=rand() % (int) (pow(2, 32));
        act_taken=eval_act( alu_out,  branch_cond);
        
        if(act_taken!=pred_taken){
            if(act_taken) npc_corr=pred_addr;
            else npc_corr=pred_pc+4;   
        
        
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
        std::cout<<"npc_in:"<<npc_in<<std::endl;
        std::cout<<"npc:"<<model.npc<<std::endl;
        std::cout<<"npc_corr:"<<npc_corr<<std::endl;
        std::cout<<"pred_pc+4:"<<pred_pc+4<<std::endl;
        std::cout<<"pred_addr:"<<pred_addr<<std::endl;

        //REQUIRE((uint32_t) model.npc == (uint32_t) npc_in);
        REQUIRE((uint32_t) model.npc == (uint32_t) npc_corr);
        REQUIRE(model.rstn_out == 0); //Expect actual 0 output here, not High Z
        }
    }
}
