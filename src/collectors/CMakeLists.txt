project(collectors)

add_library(collectors exchange.cpp exchange.h)

target_link_libraries(collectors
        pthread
        rt
        dl
        boost_serialization
        boost_system
        boost_filesystem
        boost_thread
        tomcrypt
        crypto
        crypt
        simdjson
)

find_package(Boost REQUIRED COMPONENTS program_options)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(collectors ${Boost_LIBRARIES})
endif ()

find_package(OpenSSL REQUIRED)
if (OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(collectors ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
endif ()