set(CURRENT_TARGET core)
add_library(${CURRENT_TARGET} SHARED)

string(TOUPPER ${CURRENT_TARGET} U_CTARGET)

add_subdirectory(math)

set(CORE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
)

set(CORE_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/CubeData.hpp
	${CMAKE_CURRENT_LIST_DIR}/Global_Props.hpp
	${CMAKE_CURRENT_LIST_DIR}/Preprocess_Definitions.hpp
	${CMAKE_CURRENT_LIST_DIR}/Struct_Definitions.hpp
	${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${CORE_HEADERS}
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${CORE_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${PRIMARY_INCLUDE_DIR}
)

GENERATE_EXPORT_HEADER(${CURRENT_TARGET}
             BASE_NAME ${CURRENT_TARGET}
             EXPORT_MACRO_NAME ${U_CTARGET}_EXPORT
             EXPORT_FILE_NAME ${CURRENT_TARGET}_export.hpp
             STATIC_DEFINE ${U_CTARGET}_BUILT_AS_STATIC
)

groupSources()
