project(trade_lab_python_bindings)



find_package(pybind11 REQUIRED)
pybind11_add_module(trade_lab_python_bindings SHARED main-bindings.cpp)

target_link_libraries(trade_lab_python_bindings PRIVATE collectors trading-structures bar-aggregators db-connectors analysis pybind11::module)

target_include_directories(trade_lab_python_bindings PRIVATE
    ${CMAKE_SOURCE_DIR}/src/collectors
    ${CMAKE_SOURCE_DIR}/src/trading-structures
    ${CMAKE_SOURCE_DIR}/src/bar-aggregators
    ${CMAKE_SOURCE_DIR}/src/db-connectors
    ${CMAKE_SOURCE_DIR}/src/analysis
)