add_subdirectory(trading_structures)
add_subdirectory(lib/rapidcsv)
add_subdirectory(bar_aggregators)

add_executable(trade-lab main.cpp)

target_link_libraries(trade-lab trading-structures rapidcsv bar-aggregators)