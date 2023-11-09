#include <catch2/catch_test_macros.hpp>
#include <VBranch_Manager.h>
#include <cstdint>
#include <stdlib.h>  
#include <math.h>

TEST_CASE("") {

    VBranch_Manager model;
   
    //Initialize Module
    model.rstn = 1;
    model.clk = 0;
    model.eval();
    model.rstn_h = 0;
    model.eval();
    
    
    //Test Module
    for (int i = 0; i < 1000; i++) {
        
    }
}