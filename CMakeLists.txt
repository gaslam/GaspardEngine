cmake_minimum_required(VERSION 3.16)


if(MSVC) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
add_compile_options(/arch:AVX2)
endif()

project(GaspardEngine)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME})
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${ENGINE_SOURCES}")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE "include/pch.h")

# set warning level

if(MSVC)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /WX)
else()
target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()