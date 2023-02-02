#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <set>
#include <stdexcept>
#include "Buffer.hpp"
#include "VertexAttribManager.hpp"
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
	using BufferIndex_t = unsigned int;

	unsigned int id;
	std::unordered_map<GLenum, Buffer*> boundBuffers;
	std::unordered_map<BufferIndex_t, Buffer*> vertexBuffers;
	std::shared_ptr<VertexAttribManager> vam;

	void hollowBind() const;

	void hollowUnbind() const;

	void unbindBuffer(GLenum bufferType);

	void bindBuffer(Buffer& buffer, GLenum bufferType);

	bool boundBuffersHasBufferType(GLenum bufferType);

	inline auto findVertexBuffer(Buffer& buffer) {
		auto i = begin(vertexBuffers);
		for (;i != end(vertexBuffers); i++) {
			if (i->second == &buffer) return i;
		}
		return i;
	}

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


	void bindIndexBuffer(Buffer& buffer);
	void bindVertexBuffer(Buffer& buffer, unsigned int bufferIndex = 0);
	void unbindVertexBuffer(Buffer& buffer);

	void addReal(unsigned int size, unsigned int bufferIndex = 0);
	void attributeFormat();
	void attributeBinding();
	void attributePointer();

};

