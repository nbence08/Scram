set(CURRENT_TARGET IO)
add_library(${CURRENT_TARGET})

set_target_properties(${CURRENT_TARGET} PROPERTIES LINKER_LANGUAGE CXX)

set(IO_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/IO.cpp
)

set(IO_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/IO.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${IO_HEADERS}
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${IO_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

target_link_libraries(${CURRENT_TARGET} PRIVATE core GPU components)

# copyHeadersToInclude(${IO_SOURCES})
groupSources()
