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
	unsigned int getId() const;

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	Buffer(Buffer&& other) noexcept;
	Buffer& operator=(Buffer&& other) noexcept;


	Buffer();
	~Buffer();

	void setVao(VertexArray* vao);
	VertexArray* getVao();
	GLenum getBufferType();

	void bufferData(const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);

	void setBufferType(GLenum bufferType);
};

