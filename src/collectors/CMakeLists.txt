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
)