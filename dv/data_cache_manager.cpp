#include <cstdint>

#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>

#include <VData_Cache_Manager.h>

static void eval(bool dcache_en, bool dcache_rw, bool mem_request, bool mem_write_enable, bool mem_busy) {
    auto& dcache_man {nyu::getDUT<VData_Cache_Manager>()};
    
    dcache_man.dcache_en = dcache_en;
    dcache_man.dcache_rw = dcache_rw;
    dcache_man.mem_request = mem_request;
    dcache_man.mem_write_enable = mem_write_enable;
    dcache_man.mem_busy = mem_busy;
    nyu::eval(dcache_man);

    INFO ("Testing dcache_en = " << dcache_en << ", dcache_rw = " << dcache_rw << ", mem_request = " << mem_request << ", mem_write_enable = " << mem_write_enable <<", and mem_busy = " << mem_busy);

    REQUIRE((bool) dcache_man.write_enable == (bool) (dcache_en & dcache_rw));
    REQUIRE((bool) dcache_man.read_enable == (bool) (dcache_en & !dcache_rw));
    REQUIRE((bool) dcache_man.isBurst == 0);
    REQUIRE((bool) dcache_man.mem_ready == (bool) !mem_busy);
    REQUIRE((bool) dcache_man.wEn == (bool) (mem_request & mem_write_enable));
    REQUIRE((bool) dcache_man.rEn == (bool) (mem_request & !mem_write_enable));
}

static void test() {
    for (int dcache_en {0}; dcache_en < 2; ++dcache_en)
        for (int dcache_rw {0}; dcache_rw < 2; ++dcache_rw)
            for (int mem_request {0}; mem_request < 2; ++mem_request)
                for (int mem_write_enable {0}; mem_write_enable < 2; ++mem_write_enable)
                    for (int mem_busy {0}; mem_busy < 2; ++mem_busy)
                        eval(dcache_en, dcache_rw, mem_request, mem_write_enable, mem_busy);
}

TEST_CASE("Data_Cache_Manager, Output Logic"){
    test();
}