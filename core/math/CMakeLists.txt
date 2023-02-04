target_sources(Scram
	PUBLIC

	# math
	${CMAKE_CURRENT_LIST_DIR}/linear_algebra.hpp
	${CMAKE_CURRENT_LIST_DIR}/Math_Functions.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix3.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix3.hpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix4.hpp
	${CMAKE_CURRENT_LIST_DIR}/Quaternion.cpp
	${CMAKE_CURRENT_LIST_DIR}/Quaternion.hpp
	${CMAKE_CURRENT_LIST_DIR}/Vector2.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector2.hpp
	${CMAKE_CURRENT_LIST_DIR}/Vector3.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector3.hpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector4.hpp
)

target_include_directories(Scram
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
 )
