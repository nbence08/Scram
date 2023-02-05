#pragma once
#include <set>
#include "GL/glew.h"

class VertexArray;

static bool isValidUsage(GLenum usage);

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

