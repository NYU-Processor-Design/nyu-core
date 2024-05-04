#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VBranch_Manager.h>


static void eval(auto& bman, bool pred_taken, bool act_taken, std::uint32_t pred_pc, std::uint32_t pred_addr) {

    std::uint32_t npc = 0;

    bman.clk = 0;
    bman.rstn = 1;
    nyu::eval(bman);

    bman.clk = 1;
    bman.rstn = 1;

    bman.pred_taken = pred_taken;
    bman.act_taken = act_taken;
    bman.pred_pc = pred_pc;
    bman.pred_addr = pred_addr;
    nyu::eval(bman);
    
    INFO("Testing pred_taken = " << pred_taken << ", act_taken = " << act_taken << ", pred_pc = " << pred_pc << ", and pred_addr = " << pred_addr);

    if ((act_taken == pred_taken) && pred_taken) npc = pred_addr;
    else if ((act_taken != pred_taken) && act_taken) npc = pred_addr;
    else npc = pred_pc + 4;

    REQUIRE((bool) bman.flush == (bool) (pred_taken != act_taken));
    REQUIRE((uint32_t) bman.npc == (uint32_t) (npc));    
}   

static void init(auto& bman) {
    //Initialize Module
    bman.rstn = 1;
    bman.clk = 0;
    nyu::eval(bman);
    bman.rstn = 0;
    nyu::eval(bman);

    //Move out of starting conditions
    bman.clk = 0;
    nyu::eval(bman);
    bman.clk = 1;
    bman.rstn = 1;
    nyu::eval(bman);
}

static void test() {
    auto& bman {nyu::getDUT<VBranch_Manager>()};
    
    init(bman);
    for(std::uint32_t pred_pc {0}; pred_pc < 48; ++pred_pc)
        for(std::uint32_t pred_addr {0}; pred_addr < 48; ++pred_addr)
            for(int pred_taken {0}; pred_taken < 2; ++pred_taken)
                for(int act_taken {0}; act_taken < 2; ++act_taken)
                    eval(bman, pred_taken, act_taken, pred_pc, pred_addr);
    
    init(bman);
    for(std::uint32_t pred_pc {1}; pred_pc; pred_pc <<= 1)
        for(std::uint32_t pred_addr {1}; pred_addr; pred_addr <<=1)
            for(int pred_taken {0}; pred_taken < 2; ++pred_taken)
                for(int act_taken {0}; act_taken < 2; ++act_taken)
                    eval(bman, pred_taken, act_taken, pred_pc, pred_addr);
}

TEST_CASE("Branch Manager, Flushing and Predictions") {
    test();
}
