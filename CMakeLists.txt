cmake_minimum_required(VERSION 3.10)
project(Scram VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SCRAM_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PRIMARY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(use_double_opt "use double as real type" OFF)
option(verbose "verbose" OFF)

include(BuildFunctions.cmake)
include(GenerateExportHeader)

#TODO: make all generateExportHeader project names uppercase, but only in function calls

if(use_double_opt)
	add_compile_definitions(USE_DOUBLE)
else()
	add_compile_definitions(USE_FLOAT)
endif()

if(APPLE)
	add_compile_definitions(APPLE)
elseif(WIN32)
	add_compile_definitions(WINDOWS)
elseif(UNIX)
	add_compile_definitions(UNIX)
endif()

add_subdirectory(core)
add_subdirectory(components)
add_subdirectory(io)
add_subdirectory(rendering)
add_subdirectory(GPU)
add_subdirectory(resources)
add_subdirectory(main)
