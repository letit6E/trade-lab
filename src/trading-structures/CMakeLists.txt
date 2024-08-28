project(trading-structures)

add_library(trading-structures trade.cpp trade.h
        bar.cpp
        bar.h
        bar_aggregator.h
        footprint.cpp
        footprint.h
        abstract_bar_aggregator.h
        aggregator_rule.h
        aggregator_rule.cpp
        trading_spec.cpp
        trading_spec.h
        aggregator_builder.h
        aggregator_bar_builder.cpp
        aggregator_bar_builder.h
        statistic.h
        stock_bar_aggregator.h
)

target_include_directories(trading-structures SYSTEM PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})