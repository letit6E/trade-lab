add_subdirectory(lib/googletest)

add_definitions(-DRESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(tests main.cpp src/trade_tests.cpp
        src/bar_tests.cpp
        src/time_aggregator_tests.cpp
        src/tick_aggregator_tests.cpp
        src/volume_aggregator_tests.cpp)

target_link_libraries(tests gtest gtest_main trading-structures bar-aggregators)

add_test(NAME AllTests COMMAND tests)