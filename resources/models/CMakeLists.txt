set(RESOURCES
   box.blend
   box.blend1
   box.glb
   bsg_pegasus.glb
   bsg_pegasus.mtl
)

foreach(res ${RESOURCES})

    file(COPY ${res} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

endforeach()
