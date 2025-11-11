# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(mbed)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

set(mbedtls_home ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)
set(mbedtls_path ${mbedtls_home})

message(STATUS "current path: ${mbedtls_path}")
add_subdirectory(${mbedtls_path} mbedtls)

add_library(entry SHARED hello.cpp)

set(libmbedtls_path ${mbedtls_home}/harmony/lib/${OHOS_ARCH})
set(libmbedtls ${libmbedtls_path}/libmbedtls_all.a)
set(CMAKE_SHARED_LINKER_FLAGS "-shared -O3 -flto")

find_library(
    hilog-lib
    hilog_ndk.z
)

target_link_libraries(entry PUBLIC ${libmbedtls} libace_napi.z.so ${hilog-lib} libace_napi.z.so libc++.a)
