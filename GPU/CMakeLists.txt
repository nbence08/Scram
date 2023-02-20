set(CURRENT_TARGET GPU)
add_library(${CURRENT_TARGET})

add_subdirectory(interfaces)
add_subdirectory(opengl)

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE glew32 OpenGL32 core components)

groupSources()
