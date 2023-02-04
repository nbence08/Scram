set(CORE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CubeData.hpp
	${CMAKE_CURRENT_LIST_DIR}/Global_Props.hpp
	${CMAKE_CURRENT_LIST_DIR}/Preprocess_Definitions.hpp
	${CMAKE_CURRENT_LIST_DIR}/Struct_Definitions.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${CORE_SOURCES}
)

add_subdirectory(math)
add_subdirectory(opengl)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

copyHeadersToInclude(${CORE_SOURCES})
