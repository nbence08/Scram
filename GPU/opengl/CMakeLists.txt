set(OPENGL_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/Buffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/Framebuffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/OpenGLContext.cpp
	${CMAKE_CURRENT_LIST_DIR}/Renderbuffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/ShaderProgram.cpp
	${CMAKE_CURRENT_LIST_DIR}/Texture2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/TextureCube.cpp
	${CMAKE_CURRENT_LIST_DIR}/TextureUnit.cpp
	${CMAKE_CURRENT_LIST_DIR}/UniformProvider.cpp
	${CMAKE_CURRENT_LIST_DIR}/VertexArray.cpp
	${CMAKE_CURRENT_LIST_DIR}/VertexAttribManager.cpp
)

set(OPENGL_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/Buffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Framebuffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/OpenGLContext.hpp
	${CMAKE_CURRENT_LIST_DIR}/Renderbuffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/ShaderProgram.hpp
	${CMAKE_CURRENT_LIST_DIR}/Texture2D.hpp
	${CMAKE_CURRENT_LIST_DIR}/TextureCube.hpp
	${CMAKE_CURRENT_LIST_DIR}/TextureUnit.hpp
	${CMAKE_CURRENT_LIST_DIR}/UniformProvider.hpp
	${CMAKE_CURRENT_LIST_DIR}/VertexArray.hpp
	${CMAKE_CURRENT_LIST_DIR}/VertexAttribManager.hpp
)

target_sources(${CURRENT_TARGET}
	PUBLIC
	${OPENGL_HEADERS}
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${OPENGL_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(shaders)
