cmake_minimum_required(VERSION 3.10)
project(Scram VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PRIMARY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(use_double_opt "use double as real type" OFF)
option(verbose "verbose" OFF)

function(copyHeadersToInclude <files>...)
	foreach(s ${ARGN})
		string(REGEX MATCH ".*\.hpp" isHeader ${s} )
		if(isHeader)
			if(verbose)
				message("copying header "${s}" to "${PRIMARY_INCLUDE_DIR})
			endif()
			file(COPY ${s} DESTINATION ${PRIMARY_INCLUDE_DIR})
		endif()

	endforeach()
endfunction()

set(CURRENT_TARGET Scram)
add_executable(Scram)
add_subdirectory(main)
add_subdirectory(resources)

if(use_double_opt)
	add_compile_definitions(USE_DOUBLE)
else()
	add_compile_definitions(USE_FLOAT)
endif()

target_include_directories(${CURRENT_TARGET}
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_directories(Scram PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_directories(Scram PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/Debug)

target_link_libraries(Scram PUBLIC glew32 glfw3 assimp OpenGL32 core IO GPU)

set(CURRENT_TARGET core)
add_library(core)
target_include_directories(${CURRENT_TARGET}
	PUBLIC 
	${PRIMARY_INCLUDE_DIR}
	${CMAKE_CURRENT_LIST_DIR}
)
add_subdirectory(components)
add_subdirectory(core)

set(CURRENT_TARGET IO)
add_library(IO INTERFACE)
target_include_directories(${CURRENT_TARGET}
	INTERFACE 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}
)
add_subdirectory(io)

set(CURRENT_TARGET GPU)
add_library(GPU)
target_include_directories(${CURRENT_TARGET}
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}
)
add_subdirectory(rendering)
add_subdirectory(shaders)


set(SCRAM_SRC_ROOT "${CMAKE_SOURCE_DIR}")
file(GLOB_RECURSE SCRAM_SRC
    "${SCRAM_SRC_ROOT}/*.hpp"
	"${SCRAM_SRC_ROOT}/*.cpp"
	"${SCRAM_SRC_ROOT}/*.h"
	"${SCRAM_SRC_ROOT}/*.c"
)

file(GLOB_RECURSE SCRAM_SHADERS
	"${SCRAM_SRC_ROOT}/*.frag"
    "${SCRAM_SRC_ROOT}/*.vert"
    "${SCRAM_SRC_ROOT}/*.geom"
)

source_group(TREE ${SCRAM_SRC_ROOT} FILES ${SCRAM_SRC} ${SCRAM_SHADERS})
