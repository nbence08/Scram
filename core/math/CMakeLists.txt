target_sources(Scram
	PUBLIC

	# math
	${CMAKE_CURRENT_LIST_DIR}/linear_algebra.hpp
	${CMAKE_CURRENT_LIST_DIR}/Math_Functions.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix3.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix3.h
	${CMAKE_CURRENT_LIST_DIR}/Matrix4.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4.h
	${CMAKE_CURRENT_LIST_DIR}/Quaternion.cpp
	${CMAKE_CURRENT_LIST_DIR}/Quaternion.h
	${CMAKE_CURRENT_LIST_DIR}/Vector2.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector2.h
	${CMAKE_CURRENT_LIST_DIR}/Vector3.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector3.h
	${CMAKE_CURRENT_LIST_DIR}/Vector4.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4.h
)

target_include_directories(Scram
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
 )
