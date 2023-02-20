set(CURRENT_TARGET rendering)
add_library(${CURRENT_TARGET})

set(RENDERING_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/IncRenderer.cpp
	${CMAKE_CURRENT_LIST_DIR}/Pass.cpp
	${CMAKE_CURRENT_LIST_DIR}/PassBuilder.cpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
)

set(RENDERING_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/IncRenderer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Pass.hpp
	${CMAKE_CURRENT_LIST_DIR}/PassBuilder.hpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${RENDERING_HEADERS})

target_sources(${CURRENT_TARGET}
	PRIVATE
	${RENDERING_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib/Debug)
target_link_libraries(${CURRENT_TARGET} PRIVATE core components GPU IO)

groupSources()
