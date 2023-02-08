#include "Renderbuffer.hpp"

namespace ScOpenGL {

inline unsigned int Renderbuffer::getId() { return id; }

Renderbuffer::Renderbuffer() {
	glGenRenderbuffers(1, &id);
}

Renderbuffer& Renderbuffer::operator=(Renderbuffer&& other) noexcept {
	this->id = other.id;
	other.id = 0;
	return *this;
};

Renderbuffer::Renderbuffer(Renderbuffer&& other) noexcept {
	*this = std::forward<Renderbuffer>(other);
};

Renderbuffer::~Renderbuffer() {
	glDeleteRenderbuffers(1, &id);
}

void Renderbuffer::bind() {
	glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void Renderbuffer::unbind() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

}
