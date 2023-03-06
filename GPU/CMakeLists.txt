set(CURRENT_TARGET GPU)
add_library(${CURRENT_TARGET} SHARED)

add_subdirectory(Interface)
add_subdirectory(opengl)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/bin)
target_link_libraries(${CURRENT_TARGET} PUBLIC glew32 glfw3 OpenGL32)
target_link_libraries(${CURRENT_TARGET} PRIVATE core)

GENERATE_EXPORT_HEADER(${CURRENT_TARGET}
             BASE_NAME ${CURRENT_TARGET}
             EXPORT_MACRO_NAME ${CURRENT_TARGET}_EXPORT
             EXPORT_FILE_NAME ${CURRENT_TARGET}_export.hpp
             STATIC_DEFINE ${CURRENT_TARGET}_BUILT_AS_STATIC
)

groupSources()
