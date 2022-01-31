#include "VertexAttribManager.h"

VertexAttribManager::VertexAttribManager() {
	stride = 0;
	vao = nullptr;
	attributed = false;
}

void VertexAttribManager::addReal(int size) {
	if (size > 4 || size < 1) {
		throw std::runtime_error("Attrib size must be 1,2,3 or 4!");
	}
	attributed = false;

	stride += sizeof(real_t) * size;

	glEnableVertexAttribArray((GLint)attribs.size());
	
	attribs.emplace_back((GLint) size, GL_REAL, (GLint)sizeof(real_t));
}

//glVertexAttribPointer calls
void VertexAttribManager::attributeFormat() {
	unsigned long int offset = 0;

	/*for (unsigned i = 0; i < attribs.size(); i++) {
		auto attrib = attribs[i];
		glVertexAttribFormat(i, attrib.size, attrib.type, GL_FALSE, offset);
		offset += attribs[i].unitSize * attribs[i].size;
	}*/
}

void VertexAttribManager::attributePointer() {
	if (attributed) return;

	unsigned long int stride = 0;

	for (int i = 0; i < attribs.size(); i++) {
		stride += attribs[i].size *attribs[i].unitSize;
	}

	unsigned long int offset = 0;

	for (unsigned i = 0; i < attribs.size(); i++) {
		auto attrib = attribs[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrib.size, attrib.type, GL_FALSE, stride, (const void*)offset);
		
		offset += attribs[i].unitSize * attribs[i].size;
	}
	attributed = true;
}