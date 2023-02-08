#include "VertexAttribManager.hpp"
#include "VertexArray.hpp"
#include "Preprocess_Definitions.hpp"

namespace ScOpenGL {
	VertexAttribManager::VertexAttribManager() {
		stride = 0;
		vao = nullptr;
		attributed = false;
	}

	unsigned int VertexAttribManager::getStride(unsigned int bufferIndex) {
		unsigned accu = 0;
		for (const auto& attrib : attribs) {
			if (attrib.bufferIndex == bufferIndex) {
				accu += attrib.size * attrib.unitSize;
			}
		}
		return accu;
	}

	unsigned int VertexAttribManager::getRelativeOffset(unsigned int attribIndex) {

		unsigned accu = 0;
		unsigned int bufferIndex = attribs[attribIndex].bufferIndex;
		for (int i = 0; i < attribIndex; i++) {
			const auto& attrib = attribs[i];
			if (attrib.bufferIndex == bufferIndex) {
				accu += attrib.size * attrib.unitSize;
			}
		}
		return accu;
	}

	void VertexAttribManager::addReal(unsigned int size, unsigned int bufferIndex) {
		if (size > 4 || size < 1) {
			throw std::invalid_argument("Attrib size must be 1,2,3 or 4!");
		}
		attributed = false;

		stride += sizeof(real_t) * size;

		glEnableVertexArrayAttrib(vao->getId(), (GLint)attribs.size());

		attribs.emplace_back((GLint)size, GL_REAL, (GLint)sizeof(real_t), bufferIndex);
	}

	//glVertexAttribPointer calls
	void VertexAttribManager::attributeFormat() {
		for (unsigned i = 0; i < attribs.size(); i++) {
			auto attrib = attribs[i];
			glVertexArrayAttribFormat(vao->getId(), i, attrib.size, attrib.type, GL_FALSE, getRelativeOffset(i));
		}
	}

	void VertexAttribManager::attributeBinding() {
		for (unsigned i = 0; i < attribs.size(); i++) {
			auto attrib = attribs[i];
			glVertexArrayAttribBinding(vao->getId(), i, attrib.bufferIndex);
		}
	}

	void VertexAttribManager::attributePointer() {
		attributeFormat();
		attributeBinding();
	}

}
