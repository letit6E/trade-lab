add_subdirectory(trading-structures)
add_subdirectory(bar-aggregators)
add_subdirectory(collectors)
add_subdirectory(db-connectors)
add_subdirectory(lib/simdjson)
add_subdirectory(lib/libpqxx)

add_executable(trade-lab main.cpp)
target_link_libraries(trade-lab collectors trading-structures bar-aggregators db-connectors simdjson pqxx)

add_definitions(-DLTM_DESC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
