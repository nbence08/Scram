#pragma once
#include "GL/glew.h"
#include "core/Preprocess_Definitions.hpp"
#include "core/OpenGL/VertexArray.hpp"

#include <vector>
#include <stdexcept>

namespace ScOpenGL {
	struct VertexAttribProps {
		GLint size;
		GLenum type;
		GLint unitSize;
		GLuint bufferIndex;

		VertexAttribProps(GLint size, GLenum type, GLint unitSize, GLuint bufferIndex) : size(size), type(type), unitSize(unitSize), bufferIndex(bufferIndex) {}
	};
}

namespace ScOpenGL {
	class VertexArray;

	class VertexAttribManager {
		std::vector<VertexAttribProps> attribs;
		int stride;
		VertexArray* vao;
		bool attributed;

		unsigned int getStride(unsigned int bufferIndex = 0);
		unsigned int getRelativeOffset(unsigned int attribIndex);
	public:
		VertexAttribManager();

		void addReal(unsigned int size, unsigned int bufferIndex = 0);

		//glVertexAttribPointer calls
		void attributeFormat();

		void attributeBinding();

		//in the future support can be added for multiple buffers for e.g. VertexBuffer
		void attributePointer();

		friend VertexArray;
	};
}
