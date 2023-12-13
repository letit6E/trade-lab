add_subdirectory(lib/googletest)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(trade_tests main.cpp src/trade_tests.cpp)

target_link_libraries(trade_tests gtest gtest_main trading-structures)

add_test(NAME AllTestsInTradeTests COMMAND trade_tests)

