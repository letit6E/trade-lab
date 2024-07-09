target_include_directories("${target}" ${public} [==[$<BUILD_INTERFACE:/home/letit6e/trade-lab/src/lib/simdjson/include>]==] ${private} [==[$<BUILD_INTERFACE:/home/letit6e/trade-lab/src/lib/simdjson/src>]==])
target_compile_features("${target}" ${public} [==[cxx_std_11]==])
target_compile_options("${target}" ${private} [==[-mno-avx256-split-unaligned-load]==] [==[-mno-avx256-split-unaligned-store]==])
target_compile_options("${target}" ${private} [==[$<$<CONFIG:DEBUG>:-Og>]==])
target_link_libraries("${target}" ${public} [==[Threads::Threads]==])
target_compile_definitions("${target}" ${public} [==[SIMDJSON_THREADS_ENABLED=1]==])
