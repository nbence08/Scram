#include "Buffer.hpp"
#include <stdexcept>

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

bool isValidUsage(GLenum usage) {
	return (validUsages.find(usage) != validUsages.end());
}

Buffer::Buffer(Buffer&& other) noexcept{
	*this = std::forward<Buffer>(other);
}

unsigned int Buffer::getId() const { return id; }

Buffer& Buffer::operator=(Buffer&& other) noexcept {
	if(this == &other) return *this;
	this->id = other.id;
	this->vao = other.vao;
	this->bufferType = other.bufferType;

	other.id = 0;
	other.vao = nullptr;
	other.bufferType = 0;
	return *this;
}

Buffer::Buffer() {
	glGenBuffers(1, &id);
	bufferType = 0;
	vao = nullptr;
}

Buffer::~Buffer() {
	//TODO: write method in vertexArray which debinds this buffer if bound
	glDeleteBuffers(1, &id);
}

void Buffer::setVao(VertexArray* vao) {
	this->vao = vao;
}

VertexArray* Buffer::getVao() { return vao; }
GLenum Buffer::getBufferType() { return bufferType; }

void Buffer::bufferData(const void* data, GLsizeiptr size, GLenum usage) {
	if (!isValidUsage(usage)) {
		throw std::runtime_error("Invalid usage: " + usage);
	}
	glNamedBufferData(id, size, data, usage);
}

void Buffer::setBufferType(GLenum bufferType) {
	this->bufferType = bufferType;
}
