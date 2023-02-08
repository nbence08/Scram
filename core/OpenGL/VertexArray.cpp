#include "VertexArray.hpp"

namespace ScOpenGL {

	VertexArray::VertexArray(VertexArray&& vao) noexcept {
		*this = std::forward<VertexArray>(vao);
	}

	VertexArray& VertexArray::operator=(VertexArray&& vao) noexcept {
		if (this == &vao) return *this;
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

		//these need to be called because glVertexArrayVertexBuffer won't accept this vertexArray as existing vaoobj otherwise
		this->hollowBind();
		this->hollowUnbind();
	}

	VertexArray::~VertexArray() {
		if (boundArray == id) unbind();
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::hollowBind() const {
		if (boundArray == id) return;
		glBindVertexArray(id);
	}

	void VertexArray::hollowUnbind() const {
		if (boundArray == id) return;
		glBindVertexArray(boundArray);
	}

	void VertexArray::unbindBuffer(GLenum bufferType) {
		this->boundBuffers.erase(bufferType);
	}

	//TODO: Possibly has bugs with setting boundBuffers
	void VertexArray::bindBuffer(ScOpenGL::Buffer& buffer, GLenum bufferType) {
		if (bufferType == GL_ARRAY_BUFFER) {
			bindVertexBuffer(buffer);
			return;
		}
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

	void VertexArray::bindVertexBuffer(ScOpenGL::Buffer& buffer, unsigned int bufferIndex) {

		if (buffer.getVao() == this || buffer.getBufferType() == GL_VERTEX_ARRAY) return;
		if (findVertexBuffer(buffer) != end(vertexBuffers)) return;

		if (buffer.vao != this && buffer.vao != nullptr) {
			buffer.vao->unbindVertexBuffer(buffer);
		}

		auto foundVbo = vertexBuffers.find(bufferIndex);
		if (foundVbo != end(vertexBuffers)) {
			unbindVertexBuffer(*foundVbo->second);
		}

		glVertexArrayVertexBuffer(this->id, bufferIndex, buffer.getId(), 0, vam->getStride(bufferIndex));

		buffer.setVao(this);
		buffer.setBufferType(GL_ARRAY_BUFFER);

	}

	void VertexArray::unbindVertexBuffer(ScOpenGL::Buffer& buffer) {

		BufferIndex_t i = 0;
		for (; i < vertexBuffers.size(); i++) {
			if (vertexBuffers[i] == &buffer) break;
		}

		glVertexArrayVertexBuffer(id, i, 0, 0, 0);

		vertexBuffers.erase(i);
		buffer.setBufferType(0);
		buffer.setVao(nullptr);
	}

	void VertexArray::bindIndexBuffer(ScOpenGL::Buffer& buffer) {
		bindBuffer(buffer, GL_ELEMENT_ARRAY_BUFFER);
	}

	void VertexArray::addReal(unsigned int size, unsigned int bufferIndex) { vam->addReal(size, bufferIndex); }
	void VertexArray::attributeFormat() {
		vam->attributeFormat();
	}

	void VertexArray::attributeBinding() {
		vam->attributeBinding();
	}


	void VertexArray::attributePointer() {
		vam->attributePointer();
	}
}
