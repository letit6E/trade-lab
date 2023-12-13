add_subdirectory(trading_structures)
add_subdirectory(lib/rapidcsv)

add_executable(divider main.cpp)

target_link_libraries(divider trading-structures rapidcsv)