#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VBranch_Predictor.h>

static void eval(auto& bpred, std::uint8_t branch_occr, std::uint8_t branch_cond, 
bool act_taken, bool pred_taken, bool &curr_pred, bool &incorrect_pred) {
    bpred.clk = 0;
    nyu::eval(bpred);

    bpred.clk = 1;
    bpred.rstn_h = 1;
    bpred.branch_occr = branch_occr;
    bpred.act_taken = act_taken;
    bpred.pred_taken = pred_taken;
    bpred.branch_cond = branch_cond;
    nyu::eval(bpred);

    INFO("Testing branch_occr = " << (int) branch_occr << ", branch_cond = " << (int) branch_cond << ", act_taken = " << act_taken << ", and pred_taken = " << pred_taken);
    
    if (!(branch_occr & 2)) {
        REQUIRE ((bool) bpred.branch_taken == (bool) branch_occr);
        return;
    }

    INFO("Before: curr_pred = " << curr_pred << " and incorrect_pred = " << incorrect_pred);
        
    if (__builtin_parity(branch_cond) == 0) {}
    else if ((act_taken ^ pred_taken) == 0) incorrect_pred = 0;
    else if (incorrect_pred) curr_pred = !curr_pred;
    else incorrect_pred = 1;

    INFO("After: curr_pred = " << curr_pred << " and incorrect_pred = " << incorrect_pred);
    REQUIRE ((bool) bpred.branch_taken == (bool) curr_pred);
}

static void init(auto& bpred) {
    bpred.rstn_h = 1;
    bpred.clk = 0;
    nyu::eval(bpred);
    bpred.rstn_h = 0;
    nyu::eval(bpred);
}

static void test(bool pred) {
    auto& bpred {nyu::getDUT<VBranch_Predictor>()};
    
    bool curr_pred = 0;
    bool incorrect_pred = 0;

    init(bpred);

    for(std::uint8_t branch_cond {0}; branch_cond < 4; ++branch_cond)
        for(int act_taken {0}; act_taken < 2; ++act_taken)
            for(int pred_taken {0}; pred_taken < 2; ++pred_taken) {
                 if (pred) {
                    for(std::uint8_t branch_occr {2}; branch_occr < 4; ++branch_occr)
                        eval(bpred, branch_occr, branch_cond, act_taken, pred_taken, curr_pred, incorrect_pred);
                } 
                else {
                    for(std::uint8_t branch_occr {0}; branch_occr < 2; ++branch_occr)
                        eval(bpred, branch_occr, branch_cond, act_taken, pred_taken, curr_pred, incorrect_pred);
                }
            }
}

TEST_CASE("Non Prediction Instruction") { //branch_occr = 0 or 1
    test(0);
}

TEST_CASE("Prediction Instruction") { //branch_occr = 2 or 3
    test(1);
}