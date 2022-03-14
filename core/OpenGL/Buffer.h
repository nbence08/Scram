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

/// <summary>
/// Buffer class representing a buffer object in OpenGL
/// </summary>
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

