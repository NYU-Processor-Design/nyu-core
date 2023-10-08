find_package(Catch2 3 REQUIRED CONFIG)
find_package(nyu-util REQUIRED CONFIG)

add_executable(tests)
target_sources(tests PRIVATE
  alu.cpp branch_eval.cpp pc.cpp ifid.cpp memwb.cpp gpr.cpp branch_addr_calc.cpp
)
nyu_link_sv(tests PRIVATE core)
nyu_target_verilate(tests
  TOP_MODULES Alu Branch_Eval PC IFID MEMWB GPR Branch_Addr_Calc
  ARGS COVERAGE
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain nyu::covrecorder)
target_compile_features(tests PRIVATE cxx_std_23)

include(Catch)
catch_discover_tests(tests)
