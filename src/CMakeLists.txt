add_subdirectory(trading-structures)
add_subdirectory(lib/rapidcsv)
add_subdirectory(bar-aggregators)
add_subdirectory(collectors)

add_executable(trade-lab main.cpp)
target_link_libraries(trade-lab collectors trading-structures bar-aggregators)

add_definitions(-DLTM_DESC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

find_package(Boost REQUIRED COMPONENTS program_options)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(trade-lab ${Boost_LIBRARIES})
endif ()

find_package(OpenSSL REQUIRED)
if (OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(trade-lab ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
endif ()
