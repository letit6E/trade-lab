add_subdirectory(trading-structures)
add_subdirectory(lib/rapidcsv)
add_subdirectory(lib/jsoncpp/include)
add_subdirectory(lib/websocketpp)
add_subdirectory(bar-aggregators)

include_directories(lib/websocketpp)
include_directories(lib/jsoncpp/include)

add_executable(trade-lab main.cpp)

target_link_libraries(trade-lab trading-structures rapidcsv jsoncpp websocketpp bar-aggregators)

