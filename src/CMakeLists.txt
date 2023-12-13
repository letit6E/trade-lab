add_subdirectory(trading_structures)
add_subdirectory(lib/rapidcsv)

add_executable(trade-lab main.cpp)

target_link_libraries(trade-lab trading-structures rapidcsv)