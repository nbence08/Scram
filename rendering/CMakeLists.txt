target_sources( Scram
	PUBLIC
	
	${CMAKE_CURRENT_LIST_DIR}/IncRenderer.cpp
	${CMAKE_CURRENT_LIST_DIR}/IncRenderer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Pass.cpp
	${CMAKE_CURRENT_LIST_DIR}/Pass.hpp
	${CMAKE_CURRENT_LIST_DIR}/PassBuilder.cpp
	${CMAKE_CURRENT_LIST_DIR}/PassBuilder.hpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
	${CMAKE_CURRENT_LIST_DIR}/Scene.hpp
)

target_include_directories(Scram
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
 )
