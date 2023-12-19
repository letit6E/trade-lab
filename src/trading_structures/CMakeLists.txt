project(trading-structures)

add_library(trading-structures trade.cpp trade.h
        bar.cpp
        bar.h
        bar_aggregator.h
)

target_include_directories(trading-structures PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)