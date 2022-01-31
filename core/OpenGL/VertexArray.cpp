#include "VertexArray.h"

VertexArray::VertexArray(VertexArray&& vao) noexcept {
	*this = std::move(vao);
}

VertexArray& VertexArray::operator=(VertexArray&& vao) noexcept{
	this->id = vao.id;
	this->boundBuffers = std::move(vao.boundBuffers);
	this->vam = vao.vam;
	vam->vao = this;

	for (auto& el : boundBuffers) {
		el.second->vao = this;
	}

	vao.vam = nullptr;
	vao.id = 0;
	return *this;
}

VertexArray::VertexArray() {
	glGenVertexArrays(1, &id);
	vam = std::make_shared<VertexAttribManager>();
	vam->vao = this;
}

VertexArray::~VertexArray() {
	if(boundArray == id) unbind();
	glDeleteVertexArrays(1, &id);
}

void VertexArray::hollowBind() const {
	if(boundArray == id) return;
	glBindVertexArray(id);
}

void VertexArray::hollowUnbind() const {
	if(boundArray == id) return;
	glBindVertexArray(boundArray);
}

void VertexArray::unbindBuffer(GLenum bufferType) {
	this->boundBuffers.erase(bufferType);
}

//TODO: Possibly has bugs with setting boundBuffers
void VertexArray::bindBuffer(Buffer& buffer, GLenum bufferType) {
	if (isValidBufferType(bufferType)) {
		if (buffer.vao == this && buffer.bufferType == bufferType) return;
		if (buffer.vao != this && buffer.vao != nullptr) {
			buffer.vao->unbindBuffer(buffer.bufferType);
		}

		hollowBind();
		glBindBuffer(bufferType, buffer.id);

		if (boundBuffersHasBufferType(bufferType)) {
			boundBuffers[bufferType]->setVao(nullptr);
			buffer.bufferType = 0;
			boundBuffers[bufferType] = &buffer;
		}
		else {
			boundBuffers.insert({ bufferType, &buffer });
		}

		buffer.setVao(this);
		buffer.bufferType = bufferType;

		hollowUnbind();
	}
	else {
		throw std::runtime_error("Unknown buffer type:" + bufferType);
	}
}

bool VertexArray::boundBuffersHasBufferType(GLenum bufferType) {
	return boundBuffers.find(bufferType) != boundBuffers.end();
}

void VertexArray::bind() {
	boundArray = id;
	glBindVertexArray(id);
}

void VertexArray::unbind() {
	boundArray = 0;
	glBindVertexArray(0);
}

void VertexArray::bindArrayBuffer(Buffer& buffer) {
	bindBuffer(buffer, GL_ARRAY_BUFFER);
}

void VertexArray::bindIndexBuffer(Buffer& buffer) {
	bindBuffer(buffer, GL_ELEMENT_ARRAY_BUFFER);
}

void VertexArray::addReal(int size) { vam->addReal(size); }
void VertexArray::attributeFormat() {
	hollowBind();
	vam->attributeFormat(); 
	hollowUnbind();
}

void VertexArray::attributeBinding(){
	hollowBind();
	vam->attributePointer();
	hollowUnbind();
}
