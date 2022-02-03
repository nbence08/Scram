#include "Buffer.h"

Buffer::Buffer(Buffer&& other) noexcept{
	*this = std::move(other);
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
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

void Buffer::bufferData(const void* data, GLsizeiptr size, GLenum usage) {
	if (!isValidUsage(usage)) {
		throw std::runtime_error("Invalid usage: " + usage);
	}
	glNamedBufferData(id, size, data, usage);
}

