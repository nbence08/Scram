set(IO_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/IO.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${IO_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
)

copyHeadersToInclude(${IO_SOURCES})
