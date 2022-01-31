#pragma once
#include "GL/glew.h"
#include "core/Preprocess_Definitions.h"
#include "core/OpenGL/VertexArray.h"

#include <vector>
#include <stdexcept>


struct VertexAttribProps{
	GLint size;
	GLenum type;
	GLint unitSize;

	VertexAttribProps(GLint size, GLenum type, GLint unitSize): size(size), type(type), unitSize(unitSize){}
};

class VertexArray;

class VertexAttribManager{
	std::vector<VertexAttribProps> attribs;
	int stride;
	VertexArray* vao;
	bool attributed;
public:
	VertexAttribManager();

	void addReal(int size);

	//glVertexAttribPointer calls
	void attributeFormat();

	//in the future support can be added for multiple buffers for e.g. VertexBuffer
	void attributePointer();
	
	friend VertexArray;
};

