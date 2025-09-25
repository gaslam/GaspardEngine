cmake_minimum_required(VERSION 3.16)

project(GaspardEngine)
set(CMAKE_CXX_STANDARD 20)

set(PRODUCTION_BUILD ON CACHE BOOL "Make this a production build, please!!" FORCE)

if(PRODUCTION_BUILD)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION true)
else()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION false)
endif()

if(MSVC) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
add_compile_options(/arch:AVX2)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

#set folder location for resources like textures, shaders, etc..
set(ENGINE_RESOURCE_FOLDER "Resources/")
set(ENGINE_LOGS_FOLDER "Logs/")

add_compile_definitions(ENGINE_RESOURCE_FOLDER="${ENGINE_RESOURCE_FOLDER}")
add_compile_definitions(ENGINE_LOGS_FOLDER="${ENGINE_LOGS_FOLDER}")

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_RESOURCE_FOLDER}" DESTINATION ${CMAKE_BINARY_DIR}/${ENGINE_RESOURCE_FOLDER})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_LOGS_FOLDER}" DESTINATION ${CMAKE_BINARY_DIR}/${ENGINE_LOGS_FOLDER})

add_executable(${CMAKE_PROJECT_NAME})
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${ENGINE_SOURCES}")
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE "include/pch.h")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1)

if(PRODUCTION_BUILD)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

add_subdirectory("ThirdParty/glad")
add_subdirectory("ThirdParty/glfw-3.3.2")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glad glfw)

# set warning level

if(MSVC)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /WX)
else()
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
