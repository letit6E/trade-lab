project(analysis)

add_library(analysis finmetrics_calculator.cpp finmetrics_calculator.h)

target_link_libraries(analysis trading-structures)