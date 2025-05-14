add_executable(
  run_tests 
  test_arraylist.cpp
)

target_link_libraries(
  run_tests
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(run_tests)
