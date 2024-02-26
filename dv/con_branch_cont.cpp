#include <catch2/catch_test_macros.hpp>
#include <VCon_Branch_Cont.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>
#include <NyuTestUtil.hpp>

bool act_taken_result(uint32_t alu_out, uint8_t cond) {
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

static void eval(auto& con_branch_cont, bool rstn_h, std::uint8_t branch_occr, std::uint8_t branch_cond,bool pred_taken,std::uint32_t pred_pc, std::uint32_t pred_addr,std::uint32_t alu_out,std::uint32_t npc_in,bool &curr_pred, bool &incorrect_pred){
    bool act_taken=act_taken_result(alu_out,  branch_cond);

    con_branch_cont.clk=0;
    con_branch_cont.rstn=1;
    nyu::eval(con_branch_cont);

    con_branch_cont.clk=1;
    con_branch_cont.rstn=1;
    con_branch_cont.rstn_h=rstn_h;
    con_branch_cont.branch_occr=branch_occr;
    con_branch_cont.branch_cond=branch_cond;
    con_branch_cont.pred_taken=pred_taken;
    con_branch_cont.pred_pc=pred_pc;
    con_branch_cont.pred_addr=pred_addr;
    con_branch_cont.alu_out=alu_out;
    con_branch_cont.npc_in=npc_in;
    nyu::eval(con_branch_cont);

    //check passthrough values
    //REQUIRE((uint32_t con_branch_cont.npc=npc_in));

        switch(branch_cond) {
        case 0:
            REQUIRE((bool) con_branch_cont.act_taken == 0);
            break;
        case 1:
            REQUIRE((bool) con_branch_cont.act_taken == (bool) alu_out);
            break;
        case 2:
            REQUIRE((bool) con_branch_cont.act_taken != (bool) alu_out);
            break;
        case 3:
            REQUIRE((bool) con_branch_cont.act_taken == 1);
            break;
        default:
            break;
    }
    

    INFO("Testing branch_occr = " << (int) branch_occr << ", branch_cond = " << (int) branch_cond << ", act_taken = " << act_taken << ", and pred_taken = " << pred_taken);
    if (!(branch_occr & 2)) {
        REQUIRE ((bool) con_branch_cont.branch_taken == (bool) branch_occr);
        return;
    }

    INFO("Before: curr_pred = " << curr_pred << " and incorrect_pred = " << incorrect_pred);
    if (__builtin_parity(branch_cond) == 0) {}
    else if ((act_taken ^ pred_taken) == 0) incorrect_pred = 0;
    else if (incorrect_pred) curr_pred = !curr_pred;
    else incorrect_pred = 1;

    INFO("After: curr_pred = " << curr_pred << " and incorrect_pred = " << incorrect_pred);
    REQUIRE ((bool) con_branch_cont.branch_taken == (bool) curr_pred);

 
    bool flush == (bool) (pred_taken ^ act_taken);

    if (act_taken == pred_taken) {
        INFO("Testing npc output for correct prediction with pred_pc = " << pred_pc << ", and pred_addr = " << pred_addr);
        if (pred_taken) npc = pred_addr;
        else npc = pred_pc + 4;
    }
    else {
        INFO("Testing npc output for incorrect prediction with pred_pc = " << pred_pc << ", and pred_addr = " << pred_addr);
        if (act_taken) npc = pred_addr;
        else npc = pred_pc + 4;
    }
    std::uint32_t npc_corr == (uint32_t) (npc); 

    INFO("Testing npc_in = " << npc_in << "and npc_corr = " << npc_corr);
    
    if(!flush) {
        REQUIRE((uint32_t) con_branch_cont.npc == (uint32_t) npc_in);   
        REQUIRE(pipe.rstn_out == 0); //Verilator translates High Z outputs to 0 
    }

    else {
        REQUIRE((uint32_t) con_branch_cont.npc == (uint32_t) npc_corr);
        REQUIRE(pipe.rstn_out == 0); //Expect actual 0 output here, not High Z
    }
}

static void init(auto& con_branch_cont){
    //Initialize Module
    con_branch_cont.rstn=1;
    con_branch_cont.clk=1;
    nyu::eval(con_branch_cont);
    con_branch_cont.rstn=0;
    con_branch_cont.clk=0;
    nyu::eval(con_branch_cont);
}

static void test_branch_occr(std::uint8_t branch_occr){
    auto& con_branch_cont {nyu::getDUT<VCon_Branch_Cont>()};
    init(con_branch_cont);
    for(int rstn_h{0};rstn_h<2;++rstn_h)
        for(std::uint8_t branch_cond{0};branch_cond <4; ++branch_cond)
            for(int pred_taken{0};pred_taken<2;++pred_taken)
                for(std::uint32_t pred_pc {0}; pred_pc < 128; ++pred_pc)
                    for(std::uint32_t pred_addr {0}; pred_addr < 128; ++pred_addr)
                        for(std::uint32_t alu_out {0}; alu_out < 2048; ++alu_out)
                            for(std::uint32_t npc_in {0}; npc_in < 512; ++npc_in)
                                for(int curr_pred{0};curr_pred<2;++curr_pred)
                                    for(int incorrect_pred{0};incorrect_pred<2;++incorrect_pred)
                                        eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);

    for(int rstn_h{0};rstn_h<2;++rstn_h)
        for(std::uint8_t branch_cond{0};branch_cond; branch_cond<=1)
            for(int pred_taken{0};pred_taken<2;++pred_taken)
                for(std::uint32_t pred_pc {0}; pred_pc ; pred_pc<=1)
                    for(std::uint32_t pred_addr {0}; pred_addr ; pred_addr<=1)
                        for(std::uint32_t alu_out {0}; alu_out ; alu_out<=1)
                            for(std::uint32_t npc_in {0}; npc_in ; npc_in)
                                for(int curr_pred{0};curr_pred<2;++curr_pred)
                                    for(int incorrect_pred{0};incorrect_pred<2;++incorrect_pred)
                                        eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);
}   
/*
static void test_branch_cond(std::uint8_t branch_cond){
    auto& con_branch_cont {nyu::getDUT<VCon_Branch_Cont>()};
    init(con_branch_cont);
    for(int rstn_h{0};rstn_h<2;++rstn_h)
        for(std::uint8_t branch_occr{0};branch_occr <4; ++branch_occr)
            for(int pred_taken{0};pred_taken<2;++pred_taken)
                for(std::uint32_t pred_pc {0}; pred_pc < 128; ++pred_pc)
                    for(std::uint32_t pred_addr {0}; pred_addr < 128; ++pred_addr)
                        for(std::uint32_t alu_out {0}; alu_out < 2048; ++alu_out)
                            for(std::uint32_t npc_in {0}; npc_in < 512; ++npc_in)
                                for(int curr_pred{0};curr_pred<2;++curr_pred)
                                    for(int incorrect_pred{0};incorrect_pred<2;++incorrect_pred)
                                        eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);

    for(int rstn_h{0};rstn_h<2;++rstn_h)
        for(std::uint8_t branch_occr{0};branch_occr; branch_occr<=1)
            for(int pred_taken{0};pred_taken<2;++pred_taken)
                for(std::uint32_t pred_pc {0}; pred_pc ; pred_pc<=1)
                    for(std::uint32_t pred_addr {0}; pred_addr ; pred_addr<=1)
                        for(std::uint32_t alu_out {0}; alu_out ; alu_out<=1)
                            for(std::uint32_t npc_in {0}; npc_in ; npc_in)
                                for(int curr_pred{0};curr_pred<2;++curr_pred)
                                    for(int incorrect_pred{0};incorrect_pred<2;++incorrect_pred)
                                        eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);
}
*/
static void test_pred_taken(int pred_taken){
    auto& con_branch_cont {nyu::getDUT<VCon_Branch_Cont>()};
    init(con_branch_cont);
    for(int rstn_h{0};rstn_h<2;++rstn_h)
        for(std::uint8_t branch_cond{0};branch_cond <4; ++branch_cond)
                for(std::uint32_t pred_pc {0}; pred_pc < 128; ++pred_pc)
                    for(std::uint32_t pred_addr {0}; pred_addr < 128; ++pred_addr)
                        for(std::uint32_t alu_out {0}; alu_out < 2048; ++alu_out)
                            for(std::uint32_t npc_in {0}; npc_in < 512; ++npc_in)
                                for(int curr_pred{0};curr_pred<2;++curr_pred)
                                    for(int incorrect_pred{0};incorrect_pred<2;++incorrect_pred)
                                        if(pred_taken){
                                            for(std::uint8_t branch_occr{2};branch_occr <4; ++branch_occr)
                                                eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);
                                        }else{
                                            for(std::uint8_t branch_occr{0};branch_occr <2; ++branch_occr)
                                                eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);
                                        }

    for(int rstn_h{0};rstn_h<2;++rstn_h)
        for(std::uint8_t branch_cond{0};branch_cond; branch_cond<=1)
                for(std::uint32_t pred_pc {0}; pred_pc ; pred_pc<=1)
                    for(std::uint32_t pred_addr {0}; pred_addr ; pred_addr<=1)
                        for(std::uint32_t alu_out {0}; alu_out ; alu_out<=1)
                            for(std::uint32_t npc_in {0}; npc_in ; npc_in)
                                for(int curr_pred{0};curr_pred<2;++curr_pred)
                                    for(int incorrect_pred{0};incorrect_pred<2;++incorrect_pred)
                                        if(pred_taken){
                                            for(std::uint8_t branch_occr{2};branch_occr <4; ++branch_occr)
                                                eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);
                                        }else{
                                            for(std::uint8_t branch_occr{0};branch_occr <2; ++branch_occr)
                                                eval(con_branch_cont, rstn_h, branch_occr, branch_cond, pred_taken,
                                            pred_pc,  pred_addr,alu_out,npc_in,curr_pred, 
                                            incorrect_pred);
                                        }
}

TEST_CASE("Con_Branch_Cont, branch_occr 0"){
    test_branch_occr(0);
}
TEST_CASE("Con_Branch_Cont, branch_occr 1"){
    test_branch_occr(1);
}
TEST_CASE("Con_Branch_Cont, branch_occr 2"){
    test_branch_occr(2);
}
TEST_CASE("Con_Branch_Cont, branch_occr 3"){
    test_branch_occr(3);
}
TEST_CASE("Con_Branch_Cont, pred_taken 0"){
    test_pred_taken(0);
}

TEST_CASE("Con_Branch_Cont, pred_taken 1"){
    test_pred_taken(1);
}