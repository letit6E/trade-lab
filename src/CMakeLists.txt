add_subdirectory(trading-structures)
add_subdirectory(bar-aggregators)
add_subdirectory(collectors)
add_subdirectory(lib/jsoncpp)

add_executable(trade-lab main.cpp)
target_link_libraries(trade-lab collectors trading-structures bar-aggregators jsoncpp_lib)

add_definitions(-DLTM_DESC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fPIC")
