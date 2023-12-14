project(trading-structures)

add_library(trading-structures trade.cpp trade.h
        bar.cpp
        bar.h
        bar_aggregator.h
)