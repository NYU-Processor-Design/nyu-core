find_package(Catch2 3 REQUIRED CONFIG)
find_package(nyu-util REQUIRED CONFIG)

add_executable(tests)
target_sources(tests PRIVATE
  alu.cpp

  branch_addr_calc.cpp
  branch_eval.cpp
  branch_manager.cpp
  branch_predictor.cpp

  con_branch_cont.cpp
  con_ex.cpp
  con_id.cpp

  data_cache_manager.cpp
  exmem.cpp

  gpr.cpp
  idex.cpp
  ifid.cpp

  # Failing
  # l1_data_cache.cpp

  memwb.cpp
  pc.cpp
  pipeline_reset.cpp
)

nyu_link_sv(tests PRIVATE core)
nyu_target_verilate(tests
  ARGS COVERAGE TRACE_FST
  TOP_MODULES 
  Alu
  
  Branch_Addr_Calc
  Branch_Eval
  Branch_Manager
  Branch_Predictor

  Con_Branch_Cont 
  Con_EX
  Con_ID
  
  Data_Cache_Manager
  EXMEM

  GPR
  IDEX
  IFID

  # Failing
  # L1_Data_Cache

  MEMWB
  PC  
  Pipeline_Reset      
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain nyu::covrecorder)
target_compile_features(tests PRIVATE cxx_std_23)

include(Catch)
catch_discover_tests(tests)
