project(bar-aggregators)

add_library(bar-aggregators
        time_aggregator.h
        time_aggregator.cpp
        tick_aggregator.cpp
        tick_aggregator.h)

target_link_libraries(bar-aggregators trading-structures)



