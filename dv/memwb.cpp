#include <catch2/catch_test_macros.hpp>
#include <VMEMWB.h>
#include <cstdint>
#include <stdlib.h>
#include <math.h>

//This function takes an input and sign extends the number of bits specified by old_size to the number of bits specified by new_size
uint32_t sign_extend(uint32_t input, uint32_t old_size, uint32_t new_size = 32) {
    return (uint32_t) ((input & ((int) pow(2, old_size) - 1)) | (((input & ((int) pow(2, old_size - 1))) >> (old_size - 1)) * (((int) pow(2, new_size - old_size) - 1) << (old_size))));
}

TEST_CASE("rdn Passthrough") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = rand() % (int) (pow(2, 3) - 1);
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test PC Passthrough
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint8_t) model.rdn == (uint8_t) rdn_in);
    }

}

TEST_CASE("Write Back State 0") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = 0;
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test RDD Output (rdd = alu_out)
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint32_t) model.rdd == (uint32_t) alu_out);
    }

}

TEST_CASE("Write Back State 1") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = 1;
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test RDD Output (rdd = sign extend mrd[7:0])
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint32_t) model.rdd == sign_extend(mrd, 8));
    }

}


TEST_CASE("Write Back State 2") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = 2;
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test RDD Output (rdd = sign extend mrd[15:0])
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint32_t) model.rdd == sign_extend(mrd, 16));
    }

}

TEST_CASE("Write Back State 3") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = 3;
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test RDD Output (rdd = mrd[7:0])
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint32_t) model.rdd == (uint32_t) (mrd & ((int) (pow(2, 8) - 1))));
    }
}

TEST_CASE("Write Back State 4") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = 4;
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test RDD Output (rdd = mrd[15:0])
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint32_t) model.rdd == (uint32_t) (mrd & ((int) (pow(2, 16) - 1))));
    }
}

TEST_CASE("Write Back State 5") {
    VMEMWB model;
    bool clk;
    bool rstn;
    uint8_t wbs;
    uint8_t rdn_in;
    uint32_t alu_out;
    uint32_t mrd;

    for (int i = 0; i < 1000; i++) {
        rdn_in = rand() % (int) (pow(2, 5) - 1);
        wbs = 5;
        alu_out = rand() % (int) (pow(2, 32) - 1);
        mrd = rand() % (int) (pow(2, 32) - 1);
        
        //Initialize Module
        model.rstn = 1;
        model.clk = 0;
        model.eval();
        model.rstn = 0;
        model.eval();

        
        //Test RDD Output (rdd = mrd)
        model.clk = 1;
        model.rstn = 1;
        model.wbs = wbs;
        model.rdn_in = rdn_in;
        model.mrd = mrd;
        model.alu_out = alu_out;
        model.eval();
        REQUIRE((uint32_t) model.rdd == (uint32_t) mrd);
    }
}
