target_sources(Scram
	PUBLIC
	
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.h
)

target_include_directories(Scram
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
 )
