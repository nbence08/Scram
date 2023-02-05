set(CURRENT_TARGET GPU)
add_library(${CURRENT_TARGET})

add_subdirectory(opengl)
add_subdirectory(rendering)

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

groupSources()
