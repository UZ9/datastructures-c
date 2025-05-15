add_executable(
  run_tests 
  test_hashmap.cpp
)

target_link_libraries(
  run_tests
  datastructures_c_lib
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(run_tests)
