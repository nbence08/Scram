set(CURRENT_TARGET Scram)
add_executable(${CURRENT_TARGET})

target_sources(${CURRENT_TARGET}
	PRIVATE
	${SCRAM_ROOT_DIR}/BuildFunctions.cmake
)

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${PRIMARY_INCLUDE_DIR}
)

# message(${SCRAM_ROOT_DIR}/lib)
# message(${SCRAM_ROOT_DIR}/lib/Debug)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib/Debug)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib/Release)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/bin)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/bin/Debug)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/bin/Release)
target_link_libraries(${CURRENT_TARGET} PRIVATE glew32 glfw3 assimp OpenGL32 core IO GPU rendering components)

set(MAIN_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${MAIN_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
 )

groupSources()
