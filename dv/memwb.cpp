#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VMEMWB.h>


//This function takes an input and sign extends the number of bits specified by old_size to the number of bits specified by new_size
uint32_t sign_extend(uint32_t input, uint32_t old_size, uint32_t new_size = 32) {
    return (uint32_t) ((input & ((int) pow(2, old_size) - 1)) | (((input & ((int) pow(2, old_size - 1))) >> (old_size - 1)) * (((int) pow(2, new_size - old_size) - 1) << (old_size))));
}

static void eval_p(std::uint8_t wbs, std::uint8_t rdn_in, 
    std::uint32_t alu_out, std::uint32_t mrd) {
        auto& memwb {nyu::getDUT<VMEMWB>()}; 

        //Initialize Module
        memwb.rstn = 1;
        memwb.clk = 0;
        nyu::eval(memwb);
        memwb.rstn = 0;
        nyu::eval(memwb);

        
        //Test PC Passthrough
        memwb.clk = 1;
        memwb.rstn = 1;
        memwb.wbs = wbs;
        memwb.rdn_in = rdn_in;
        memwb.mrd = mrd;
        memwb.alu_out = alu_out;
        nyu::eval(memwb);
        INFO("Testing wbs + " << wbs << ", rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
        REQUIRE((uint8_t) memwb.rdn == (uint8_t) rdn_in);
    }

TEST_CASE("rdn Passthrough") {

    for(std::uint8_t wbs {0}; wbs <= 5; ++wbs)
            for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
                for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
                    for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                        eval_p(wbs, rdn_in, alu_out, mrd);

    for(std::uint8_t wbs {1}; wbs <= 5; wbs <<= 1)
            for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
                for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
                    for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                        eval_p(wbs, rdn_in, alu_out, mrd);

}

static void eval_0(std::uint8_t rdn_in, 
    std::uint32_t alu_out, std::uint32_t mrd) {
        auto& memwb {nyu::getDUT<VMEMWB>()}; 

        //Initialize Module
        memwb.rstn = 1;
        memwb.clk = 0;
        nyu::eval(memwb);
        memwb.rstn = 0;
        nyu::eval(memwb);

        
        // Test RDD Output
        memwb.clk = 1;
        memwb.rstn = 1;
        memwb.wbs = 0;
        memwb.rdn_in = rdn_in;
        memwb.mrd = mrd;
        memwb.alu_out = alu_out;
        nyu::eval(memwb);
        INFO("Testing rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
        REQUIRE((uint32_t) memwb.rdd == sign_extend(mrd, 8));
    }



TEST_CASE("Write Back State 0") {
    
    for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
        for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
            for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                eval_0(rdn_in, alu_out, mrd);

    
    for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
        for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
            for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                eval_0(rdn_in, alu_out, mrd);
}

static void eval_1(std::uint8_t rdn_in, 
    std::uint32_t alu_out, std::uint32_t mrd) {
        auto& memwb {nyu::getDUT<VMEMWB>()}; 

        //Initialize Module
        memwb.rstn = 1;
        memwb.clk = 0;
        nyu::eval(memwb);
        memwb.rstn = 0;
        nyu::eval(memwb);

        //Test RDD Output (rdd = sign extend mrd[15:0])
        memwb.clk = 1;
        memwb.rstn = 1;
        memwb.wbs = 1;
        memwb.rdn_in = rdn_in;
        memwb.mrd = mrd;
        memwb.alu_out = alu_out;
        nyu::eval(memwb);
        INFO("Testing rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
        REQUIRE((uint32_t) memwb.rdd == sign_extend(mrd, 16)); 
    }

TEST_CASE("Write Back State 1") {
 
    for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
        for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
            for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                eval_1(rdn_in, alu_out, mrd);

    
    for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
        for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
            for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                eval_1(rdn_in, alu_out, mrd);

}

static void eval_2(std::uint8_t rdn_in, 
    std::uint32_t alu_out, std::uint32_t mrd) {
        auto& memwb {nyu::getDUT<VMEMWB>()}; 

        //Initialize Module
        memwb.rstn = 1;
        memwb.clk = 0;
        nyu::eval(memwb);
        memwb.rstn = 0;
        nyu::eval(memwb);

        //Test RDD Output (rdd = mrd)
        memwb.clk = 1;
        memwb.rstn = 1;
        memwb.wbs = 2;
        memwb.rdn_in = rdn_in;
        memwb.mrd = mrd;
        memwb.alu_out = alu_out;
        nyu::eval(memwb);
        INFO("Testing rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
        REQUIRE((uint32_t) memwb.rdd == (uint32_t) mrd);
    }


TEST_CASE("Write Back State 2") {



    for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
        for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
            for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                eval_2(rdn_in, alu_out, mrd);

    
    for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
        for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
            for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                eval_2(rdn_in, alu_out, mrd);

}

  static void eval_3(std::uint8_t rdn_in, 
        std::uint32_t alu_out, std::uint32_t mrd) {
            auto& memwb {nyu::getDUT<VMEMWB>()}; 

            //Initialize Module
            memwb.rstn = 1;
            memwb.clk = 0;
            nyu::eval(memwb);
            memwb.rstn = 0;
            nyu::eval(memwb);

            //Test RDD Output (rdd = alu_out)
            memwb.clk = 1;
            memwb.rstn = 1;
            memwb.wbs = 3;
            memwb.rdn_in = rdn_in;
            memwb.mrd = mrd;
            memwb.alu_out = alu_out;
            nyu::eval(memwb);
            INFO("Testing rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
            REQUIRE((uint32_t) memwb.rdd == (uint32_t) alu_out);
        }


TEST_CASE("Write Back State 3") {
        
  
        for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
            for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
                for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                    eval_3(rdn_in, alu_out, mrd);

        
        for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
            for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
                for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                    eval_3(rdn_in, alu_out, mrd); 
        
}

static void eval_4(std::uint8_t rdn_in, 
        std::uint32_t alu_out, std::uint32_t mrd) {
            auto& memwb {nyu::getDUT<VMEMWB>()}; 

            //Initialize Module
            memwb.rstn = 1;
            memwb.clk = 0;
            nyu::eval(memwb);
            memwb.rstn = 0;
            nyu::eval(memwb);

            //Test RDD Output (rdd = mrd[7:0])
            memwb.clk = 1;
            memwb.rstn = 1;
            memwb.wbs = 4;
            memwb.rdn_in = rdn_in;
            memwb.mrd = mrd;
            memwb.alu_out = alu_out;
            nyu::eval(memwb);
            INFO("Testing rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
            REQUIRE((uint32_t) memwb.rdd == (uint32_t) (mrd & ((int) (pow(2, 8) - 1))));
        }

TEST_CASE("Write Back State 4") {

    

        for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
            for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
                for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                    eval_4(rdn_in, alu_out, mrd);

        
        for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
            for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
                for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                    eval_4(rdn_in, alu_out, mrd);
        
    }

    static void eval_5(std::uint8_t rdn_in, 
        std::uint32_t alu_out, std::uint32_t mrd) {
            auto& memwb {nyu::getDUT<VMEMWB>()}; 

            //Initialize Module
            memwb.rstn = 1;
            memwb.clk = 0;
            nyu::eval(memwb);
            memwb.rstn = 0;
            nyu::eval(memwb);

            //Test RDD Output (rdd = mrd[15:0])
            memwb.clk = 1;
            memwb.rstn = 1;
            memwb.wbs = 5;
            memwb.rdn_in = rdn_in;
            memwb.mrd = mrd;
            memwb.alu_out = alu_out;
            nyu::eval(memwb);
            INFO("Testing rdn_in = " << rdn_in << ", alu_out = " << alu_out << ", and mrd = " << mrd);
            REQUIRE((uint32_t) memwb.rdd == (uint32_t) (mrd & ((int) (pow(2, 16) - 1))));
        }


TEST_CASE("Write Back State 5") {

    

        for(std::uint8_t rdn_in {0}; rdn_in < 32; ++rdn_in)
            for(std::uint32_t alu_out {0}; alu_out < 128; ++alu_out)
                for(std::uint32_t mrd {0}; mrd < 128; ++mrd)
                    eval_5(rdn_in, alu_out, mrd);

        
        for(std::uint8_t rdn_in {1}; rdn_in < 32; rdn_in <<= 1)
            for(std::uint32_t alu_out {1}; alu_out; alu_out <<= 1)
                for(std::uint32_t mrd {1}; mrd; mrd <<= 1)
                    eval_5(rdn_in, alu_out, mrd);
       
}
