project(trading-structures)

add_library(trading-structures trade.cpp trade.h
        bar.cpp
        bar.h
        bar_aggregator.h
        footprint.cpp
        footprint.h
)

target_include_directories(trading-structures SYSTEM PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})