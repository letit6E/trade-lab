project(db-connectors)

add_library(db-connectors postgres_connector.h postgres_connector.cpp)

target_link_libraries(db-connectors trading-structures pqxx)