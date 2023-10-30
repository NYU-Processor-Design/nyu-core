#include <catch2/catch_test_macros.hpp>
#include <VBranch_Addr_Calc.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

TEST_CASE("PC No Branch") {  //Case when branch_addr = pc + imm, but branch is not taken
    VBranch_Addr_Calc model;
    bool mode;
    bool taken;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t pc_in;
    
    for (int i = 0; i < 1000; i++) {
        imm = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        mode = 0;
        taken = 0;

        model.addr_mode = mode;
        model.imm = imm;
        model.rs1d = rs1d;
        model.branch_taken = taken;
        model.eval();
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (model.pc_in + model.imm));
        REQUIRE((uint32_t) model.npc == (uint32_t) model.pc_in);
    }
}

TEST_CASE("PC Branch") { //Case when branch_addr = pc + imm, and branch is taken
    VBranch_Addr_Calc model;
    bool mode;
    bool taken;
    uint32_t imm;
    uint32_t rs1d;
    uint32_t pc_in;
    
    for (int i = 0; i < 1000; i++) {
        imm = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        mode = 0;
        taken = 1;
        
        model.addr_mode = mode;
        model.imm = imm;
        model.rs1d = rs1d;
        model.branch_taken = taken;
        model.eval();
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (model.pc_in + model.imm));
        REQUIRE((uint32_t) model.npc == (uint32_t) model.branch_addr);
    }
}


TEST_CASE("RS1D No Branch") { //Case when branch_addr = imm + rs1d, but branch is not taken
    VBranch_Addr_Calc model;
    bool mode;
    bool taken;
    uint32_t imm;
    uint32_t rs1d;
    unint32_t pc_in;
    
    for (int i = 0; i < 1000; i++) {
        imm = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        mode = 1;
        taken = 0;
        
        model.addr_mode = mode;
        model.imm = imm;
        model.rs1d = rs1d;
        model.branch_taken = taken;
        model.eval();
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (model.imm + model.rs1d));
        REQUIRE((uint32_t) model.npc == (uint32_t) model.pc_in);
    }
}

TEST_CASE("RS1D Branch") { //Case when branch_addr = rs1d, and branch is taken
    VBranch_Addr_Calc model;
    bool mode;
    bool taken;
    uint32_t imm;
    uint32_t rs1d;
    unint32_t pc_in;
    
    for (int i = 0; i < 1000; i++) {
        imm = rand() % (int) (pow(2, 32) - 1);
        rs1d = rand() % (int) (pow(2, 32) - 1);
        mode = 1;
        taken = 1;
        
        model.addr_mode = mode;
        model.imm = imm;
        model.rs1d = rs1d;
        model.branch_taken = taken;
        model.eval();
        REQUIRE((uint32_t) model.branch_addr == (uint32_t) (model.imm + model.rs1d));
        REQUIRE((uint32_t) model.npc == (uint32_t) model.branch_addr);
    }
}