#include <catch2/catch_test_macros.hpp>
#include <VBranch_Manager.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

TEST_CASE("Flush") {

    VBranch_Manager model;
   
    //Initialize Module
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn_h = 0;
    model.eval();

    //Move out of starting conditions
    model.clk = 0;
    model.eval();
    model.clk = 1;
    model.rstn = 1;
    model.eval();

    bool pred_taken;
    bool act_taken;
    uint32_t pred_pc;
    uint32_t pred_addr;
    
    //Test Module
    for (int i = 0; i < 1000; i++) {
        pred_taken = rand() % (int) (pow(2, 1) - 1);
        act_taken = rand() % (int) (pow(2, 1) - 1);
        pred_pc = rand() % (int) (pow(2, 32) - 1);
        pred_addr = rand() % (int) (pow(2, 32) - 1);
        
        model.clk = 0;
        model.eval();

        model.clk = 1;
        model.rstn = 1;

        model.pred_taken = pred_taken;
        model.act_taken = act_taken;
        model.pred_pc = pred_pc;
        model.pred_addr = pred_addr;
        model.eval();

        REQUIRE((bool) model.flush == (bool) (pred_taken ^ act_taken));
    }
}

TEST_CASE("Incorrect Prediction") {

    VBranch_Manager model;
   
    //Initialize Module
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn_h = 0;
    model.eval();

    //Move out of starting conditions
    model.clk = 0;
    model.eval();
    model.clk = 1;
    model.rstn = 1;
    model.eval();

    bool pred_taken;
    bool act_taken;
    uint32_t npc;
    uint32_t pred_pc;
    uint32_t pred_addr;
    
    //Test Module
    for (int i = 0; i < 1000; i++) {
        pred_taken = rand() % (int) (pow(2, 1) - 1);
        act_taken = ~pred_taken;
        pred_pc = rand() % (int) (pow(2, 32) - 1);
        pred_addr = rand() % (int) (pow(2, 32) - 1);
        
        model.clk = 0;
        model.eval();

        model.clk = 1;
        model.rstn = 1;

        model.pred_taken = pred_taken;
        model.act_taken = act_taken;
        model.pred_pc = pred_pc;
        model.pred_addr = pred_addr;
        model.eval();

        if (act_taken) npc = pred_pc;
        else npc = pred_pc + 4;

        REQUIRE((uint32_t) model.npc == (uint32_t) (npc));
    }
}

TEST_CASE("Correct Prediction") {

    VBranch_Manager model;
   
    //Initialize Module
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn_h = 0;
    model.eval();

    //Move out of starting conditions
    model.clk = 0;
    model.eval();
    model.clk = 1;
    model.rstn = 1;
    model.eval();

    bool pred_taken;
    bool act_taken;
    uint32_t npc;
    uint32_t pred_pc;
    uint32_t pred_addr;
    
    //Test Module
    for (int i = 0; i < 1000; i++) {
        pred_taken = rand() % (int) (pow(2, 1) - 1);
        act_taken = pred_taken;
        pred_pc = rand() % (int) (pow(2, 32) - 1);
        pred_addr = rand() % (int) (pow(2, 32) - 1);
        
        model.clk = 0;
        model.eval();

        model.clk = 1;
        model.rstn = 1;

        model.pred_taken = pred_taken;
        model.act_taken = act_taken;
        model.pred_pc = pred_pc;
        model.pred_addr = pred_addr;
        model.eval();

        if (pred_taken) npc = pred_pc;
        else npc = pred_pc + 4;

        REQUIRE((uint32_t) model.npc == (uint32_t) (npc));
    }
}
