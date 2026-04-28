cmake_minimum_required(VERSION 3.10)
project(ikerlan_test C)

set(CMAKE_C_STANDARD 11)
find_package(OpenSSL REQUIRED)


foreach(SET_NAME set_1)
    file(GLOB SOURCES ${SET_NAME}/src/*.c)
    add_executable(${SET_NAME} ${SOURCES})
    target_include_directories(${SET_NAME} PRIVATE ${SET_NAME}/include)
    target_link_libraries(${SET_NAME} PRIVATE OpenSSL::Crypto)
endforeach()

