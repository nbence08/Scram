set(CURRENT_TARGET components)
add_library(${CURRENT_TARGET} SHARED)
string(TOUPPER ${CURRENT_TARGET} U_CTARGET)

set(COMPONENT_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt

	${CMAKE_CURRENT_LIST_DIR}/ComponentBase.cpp
	
	${CMAKE_CURRENT_LIST_DIR}/Entity.cpp

	# lights
	${CMAKE_CURRENT_LIST_DIR}/DirectionalLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/PointLight.cpp
	${CMAKE_CURRENT_LIST_DIR}/SpotLight.cpp

	# visual
	${CMAKE_CURRENT_LIST_DIR}/Material.cpp
	${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp

	${CMAKE_CURRENT_LIST_DIR}/PerspectiveCamera.cpp
)

set(COMPONENT_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/ComponentBase.hpp

	${CMAKE_CURRENT_LIST_DIR}/Entity.hpp
	${CMAKE_CURRENT_LIST_DIR}/Transform.hpp

	${CMAKE_CURRENT_LIST_DIR}/DirectionalLight.hpp
	${CMAKE_CURRENT_LIST_DIR}/PointLight.hpp
	${CMAKE_CURRENT_LIST_DIR}/SpotLight.hpp

	${CMAKE_CURRENT_LIST_DIR}/Material.hpp
	${CMAKE_CURRENT_LIST_DIR}/Mesh.hpp

	${CMAKE_CURRENT_LIST_DIR}/Camera.hpp
	${CMAKE_CURRENT_LIST_DIR}/PerspectiveCamera.hpp
)

target_sources(${CURRENT_TARGET} 
	PRIVATE
	${COMPONENT_SOURCES}
)

target_sources(${CURRENT_TARGET} 
	PUBLIC
	${COMPONENT_HEADERS}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/lib)
target_link_directories(${CURRENT_TARGET} PRIVATE ${SCRAM_ROOT_DIR}/bin)
target_link_libraries(${CURRENT_TARGET} PRIVATE core GPU)


GENERATE_EXPORT_HEADER(${CURRENT_TARGET}
             BASE_NAME ${CURRENT_TARGET}
             EXPORT_MACRO_NAME ${U_CTARGET}_EXPORT
             EXPORT_FILE_NAME ${CURRENT_TARGET}_export.hpp
             STATIC_DEFINE ${U_CTARGET}_BUILT_AS_STATIC
)

groupSources()
