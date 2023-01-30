target_sources( Scram
	PUBLIC
	
	${CMAKE_CURRENT_LIST_DIR}/IncRenderer.cpp
	${CMAKE_CURRENT_LIST_DIR}/IncRenderer.h
	${CMAKE_CURRENT_LIST_DIR}/Pass.cpp
	${CMAKE_CURRENT_LIST_DIR}/Pass.h
	${CMAKE_CURRENT_LIST_DIR}/PassBuilder.cpp
	${CMAKE_CURRENT_LIST_DIR}/PassBuilder.h
	${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.h
)

target_include_directories(Scram
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
 )
