function(copyHeadersToInclude <files>...)
	foreach(s ${ARGN})
		string(REGEX MATCH ".*\.hpp" isHeader ${s} )
		if(isHeader)
			if(verbose)
				message("copying header " ${s} " to " ${PRIMARY_INCLUDE_DIR})
			endif()
			file(COPY ${s} DESTINATION ${PRIMARY_INCLUDE_DIR})
		endif()

	endforeach()
endfunction()

function(groupSources)
	set(SCRAM_SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
	file(GLOB_RECURSE SCRAM_SRC
		"${SCRAM_SRC_ROOT}/*.hpp"
		"${SCRAM_SRC_ROOT}/*.cpp"
		"${SCRAM_SRC_ROOT}/*.h"
		"${SCRAM_SRC_ROOT}/*.c"
	)

	file(GLOB_RECURSE SCRAM_SHADERS
		"${SCRAM_SRC_ROOT}/*.frag"
		"${SCRAM_SRC_ROOT}/*.vert"
		"${SCRAM_SRC_ROOT}/*.geom"
		"${SCRAM_SRC_ROOT}/*.tess"

		"${SCRAM_SRC_ROOT}/*.metal"

		"${SCRAM_SRC_ROOT}/*.psh"
		"${SCRAM_SRC_ROOT}/*.vsh"
		"${SCRAM_SRC_ROOT}/*/CMakeLists.txt"
	)

	source_group(TREE ${SCRAM_SRC_ROOT} FILES ${SCRAM_SRC} ${SCRAM_SHADERS})
endfunction()
