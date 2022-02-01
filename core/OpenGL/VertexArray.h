#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <set>
#include <stdexcept>
#include "Buffer.h"
#include "VertexAttribManager.h"
#include <memory>

class Buffer;
class VertexAttribManager;

static unsigned int boundArray = 0;

static const std::set<GLenum> validBufferTypes = {
	GL_ARRAY_BUFFER,
	GL_ATOMIC_COUNTER_BUFFER,
	GL_COPY_READ_BUFFER,
	GL_COPY_WRITE_BUFFER,
	GL_DISPATCH_INDIRECT_BUFFER,
	GL_DRAW_INDIRECT_BUFFER,
	GL_ELEMENT_ARRAY_BUFFER,
	GL_PIXEL_PACK_BUFFER,
	GL_PIXEL_UNPACK_BUFFER,
	GL_QUERY_BUFFER,
	GL_SHADER_STORAGE_BUFFER,
	GL_TEXTURE_BUFFER,
	GL_TRANSFORM_FEEDBACK_BUFFER,
	GL_UNIFORM_BUFFER
};

static bool isValidBufferType(GLenum bufferType) {
	return validBufferTypes.find(bufferType) != validBufferTypes.end();
}

class VertexArray{
	unsigned int id;
	std::unordered_map<GLenum, Buffer*> boundBuffers;
	std::shared_ptr<VertexAttribManager> vam;

	void hollowBind() const;

	void hollowUnbind() const;

	void unbindBuffer(GLenum bufferType);

	void bindBuffer(Buffer& buffer, GLenum bufferType);

	bool boundBuffersHasBufferType(GLenum bufferType);

	friend Buffer;
	friend VertexAttribManager;

public:
	VertexArray(const VertexArray& vao) = delete;
	VertexArray& operator=(const VertexArray& vao) = delete;

	VertexArray(VertexArray&& vao) noexcept;
	VertexArray& operator=(VertexArray&& vao) noexcept;

	VertexArray();
	~VertexArray();

	void bind();

	static void unbind();

	inline unsigned int getId() { return id; }

	void bindArrayBuffer(Buffer& buffer);

	void bindIndexBuffer(Buffer& buffer);

	void addReal(int size);
	void attributeFormat();
	void attributeBinding();
	void attributePointer();

};

