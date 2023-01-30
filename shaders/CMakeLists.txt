set(SHADERS
   ${CMAKE_CURRENT_LIST_DIR}/dirShadow.frag
   ${CMAKE_CURRENT_LIST_DIR}/dirShadow.vert
   ${CMAKE_CURRENT_LIST_DIR}/incremental.frag
   ${CMAKE_CURRENT_LIST_DIR}/incremental.vert
   ${CMAKE_CURRENT_LIST_DIR}/pointShadow.frag
   ${CMAKE_CURRENT_LIST_DIR}/pointShadow.vert
   ${CMAKE_CURRENT_LIST_DIR}/pointShadow.geom
   ${CMAKE_CURRENT_LIST_DIR}/postProcessor.frag
   ${CMAKE_CURRENT_LIST_DIR}/postProcessor.vert
   ${CMAKE_CURRENT_LIST_DIR}/quad.frag
   ${CMAKE_CURRENT_LIST_DIR}/quad.vert
)

foreach(res ${SHADERS})

    file(COPY ${res} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

endforeach()

target_sources(Scram PRIVATE ${SHADERS})
