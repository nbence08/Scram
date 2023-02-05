set(CURRENT_TARGET components)
add_library(${CURRENT_TARGET})

set(COMPONENT_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/ComponentBase.hpp
	${CMAKE_CURRENT_LIST_DIR}/Entity.cpp
	${CMAKE_CURRENT_LIST_DIR}/Entity.hpp
	${CMAKE_CURRENT_LIST_DIR}/Transform.hpp

	# lights
	${CMAKE_CURRENT_LIST_DIR}/DirectionalLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/DirectionalLight.hpp
	${CMAKE_CURRENT_LIST_DIR}/PointLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/PointLight.hpp
	${CMAKE_CURRENT_LIST_DIR}/SpotLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpotLight.hpp

	# visual
	${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/Camera.hpp
	${CMAKE_CURRENT_LIST_DIR}/Material.cpp
	${CMAKE_CURRENT_LIST_DIR}/Material.hpp
	${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/Mesh.hpp
	${CMAKE_CURRENT_LIST_DIR}/PerspectiveCamera.cpp
	${CMAKE_CURRENT_LIST_DIR}/PerspectiveCamera.hpp
)

target_sources(${CURRENT_TARGET} 
	PRIVATE
	${COMPONENT_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

copyHeadersToInclude(${COMPONENT_SOURCES})
groupSources()
