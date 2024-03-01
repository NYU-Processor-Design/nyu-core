find_package(Catch2 3 REQUIRED CONFIG)
find_package(nyu-util REQUIRED CONFIG)

add_executable(tests)
target_sources(tests PRIVATE
  con_ex.cpp alu.cpp branch_eval.cpp pc.cpp ifid.cpp memwb.cpp gpr.cpp exmem.cpp branch_addr_calc.cpp idex.cpp branch_predictor.cpp pipeline_reset.cpp branch_manager.cpp data_cache_manager.cpp
)
nyu_link_sv(tests PRIVATE core)
nyu_target_verilate(tests
  TOP_MODULES Con_EX Alu Branch_Eval PC IFID MEMWB GPR EXMEM Branch_Addr_Calc IDEX Branch_Predictor Pipeline_Reset Branch_Manager Data_Cache_Manager
  ARGS COVERAGE
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain nyu::covrecorder)
target_compile_features(tests PRIVATE cxx_std_23)

include(Catch)
catch_discover_tests(tests)
