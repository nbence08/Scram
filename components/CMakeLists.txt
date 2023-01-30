set(COMPONENT_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/ComponentBase.hpp
	${CMAKE_CURRENT_LIST_DIR}/Entity.cpp
	${CMAKE_CURRENT_LIST_DIR}/Entity.h
	${CMAKE_CURRENT_LIST_DIR}/Transform.h

	# lights
	${CMAKE_CURRENT_LIST_DIR}/DirectionalLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/DirectionalLight.h
	${CMAKE_CURRENT_LIST_DIR}/PointLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/PointLight.h
	${CMAKE_CURRENT_LIST_DIR}/SpotLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpotLight.h

	# visual
	${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/Camera.h
	${CMAKE_CURRENT_LIST_DIR}/Material.cpp
	${CMAKE_CURRENT_LIST_DIR}/Material.h
	${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/Mesh.h
	${CMAKE_CURRENT_LIST_DIR}/PerspectiveCamera.cpp
	${CMAKE_CURRENT_LIST_DIR}/PerspectiveCamera.h
)

target_sources(Scram 
	PUBLIC
	${COMPONENT_SOURCES}
)

target_include_directories(Scram
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

