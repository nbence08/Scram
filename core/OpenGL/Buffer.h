#pragma once
#include <set>
#include "GL/glew.h"
#include "VertexArray.h"

class VertexArray;

static std::set<GLenum> validUsages = {
	GL_STREAM_DRAW,
	GL_STREAM_READ,
	GL_STREAM_COPY,
	GL_STATIC_DRAW,
	GL_STATIC_READ,
	GL_STATIC_COPY,
	GL_DYNAMIC_DRAW,
	GL_DYNAMIC_READ,
	GL_DYNAMIC_COPY
};

static bool isValidUsage(GLenum usage) {
	return (validUsages.find(usage) != validUsages.end());
}

//TODO: modify so that buffer can count its references to the actual buffer in the GPU memory, so that when one object gets deleted, it
// doesnt pull al the others with itself, basically goes for almost every class in OpenGL filter
class Buffer{
	unsigned int id;
	VertexArray* vao;
	GLenum bufferType;


	friend VertexArray;
public:
	inline unsigned int getId() const { return id; }

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	Buffer(Buffer&& other) noexcept;
	Buffer& operator=(Buffer&& other) noexcept;


	Buffer();
	~Buffer();

	void setVao(VertexArray* vao);
	inline VertexArray* getVao() { return vao; }
	inline GLenum getBufferType() { return bufferType; }

	void bufferData(const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);

	inline void setBufferType(GLenum bufferType) {
		this->bufferType = bufferType;
	}
};

