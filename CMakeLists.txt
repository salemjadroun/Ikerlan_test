cmake_minimum_required(VERSION 3.10)
project(ikerlan_test C)
set(CMAKE_C_STANDARD 11)

find_package(OpenSSL REQUIRED)

add_library(ikerlan_common STATIC
    set_1/src/EX_1.c
    set_1/src/EX_2.c
    set_1/src/EX_3.c
    set_1/src/EX_4.c
    set_1/src/EX_5.c
    set_1/src/EX_6.c
    set_1/src/EX_7.c
    set_1/src/EX_8.c
    set_2/src/EX_9.c
    set_2/src/EX_10.c
    set_2/src/EX_11.c
    set_2/src/EX_15.c
    set_3/src/EX_18.c
    set_3/src/EX_19.c
)
target_include_directories(ikerlan_common PUBLIC set_1/include set_2/include set_3/include)
target_compile_definitions(ikerlan_common PRIVATE DOCS_DIR="${CMAKE_SOURCE_DIR}/docs")
target_link_libraries(ikerlan_common PUBLIC OpenSSL::Crypto)

add_executable(set_1 set_1/src/main.c)
target_link_libraries(set_1 PRIVATE ikerlan_common)

add_executable(set_2 set_2/src/main.c)
target_link_libraries(set_2 PRIVATE ikerlan_common)

add_executable(set_3 set_3/src/main.c)
target_link_libraries(set_3 PRIVATE ikerlan_common)