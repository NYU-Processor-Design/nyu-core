#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VBranch_Predictor.h>

static void eval(auto& bpred, std::uint8_t branch_occr, std::uint8_t branch_cond, bool act_taken, bool pred_taken) {

}

static void init(auto& bpred) {
     
}

TEST_CASE("Non Prediction Instruction") { //branch_occr = 0 or 1

    VBranch_Predictor model;

    uint8_t branch_occr;
    bool act_taken;
    bool pred_taken;
    uint8_t branch_cond;

    //Initialize Module
    model.rstn_h = 1;
    model.clk = 0;
    model.eval();
    model.rstn_h = 0;
    model.eval();

    

    //Test Module
    for (int i = 0; i < 1000; i++) {
        branch_occr = rand() % (int) (pow(2, 1));
        act_taken = rand() % (int) (pow(2, 1));
        pred_taken = rand() % (int) (pow(2, 1));
        branch_cond = rand() % (int) (pow(2, 2));

        model.clk = 0;
        model.eval();

        model.clk = 1;
        model.rstn_h = 1;
        model.branch_occr = branch_occr;
        model.act_taken = act_taken;
        model.pred_taken = pred_taken;
        model.branch_cond = branch_cond;
        model.eval();
        REQUIRE ((bool) model.branch_taken == (bool) branch_occr);
    }
}

TEST_CASE("Prediction Instruction") { //branch_occr = 2 or 3

    VBranch_Predictor model;

    uint8_t branch_occr;
    bool act_taken;
    bool pred_taken;
    uint8_t branch_cond;

    //Initialize Module
    model.rstn_h = 1;
    model.clk = 0;
    model.eval();
    model.rstn_h = 0;
    model.eval();

    //Initialize Register Tracker Variables
    bool curr_pred = 0;
    bool incorrect_pred = 0;

    //Test Module
    for (int i = 0; i < 1000; i++) {
        branch_occr = 2 + rand() % (int) (pow(2, 1));
        act_taken = rand() % (int) (pow(2, 1));
        pred_taken = rand() % (int) (pow(2, 1));
        branch_cond = rand() % (int) (pow(2, 2));
        
        model.clk = 0;
        model.eval();

        model.clk = 1;
        model.rstn_h = 1;
        model.branch_occr = branch_occr;
        model.act_taken = act_taken;
        model.pred_taken = pred_taken;
        model.branch_cond = branch_cond;

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