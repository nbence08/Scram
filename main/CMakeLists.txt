set(MAIN_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${MAIN_SOURCES}
	
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
 )

copyHeadersToInclude(${MAIN_SOURCES})
