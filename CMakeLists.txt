
cmake_minimum_required(VERSION 3.2)
project(trade-lab)
option(CodeCoverage "CodeCoverage" OFF)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wno-deprecated-register ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -Wno-deprecated-register -O0 -g -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)

add_subdirectory(src)
add_subdirectory(test)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CodeCoverage MATCHES ON)
        include(CodeCoverage)
        setup_target_for_coverage(${PROJECT_NAME}_coverage poptests coverage)
        setup_target_for_coverage_cobertura(${PROJECT_NAME}_cobertura poptests coverage --gtest_output=xml:coverage.junit.xml)
    endif()
endif()