#include <type_traits>

#include "GL/glew.h"

namespace ScOpenGL {
	/// <summary>
	/// class representing an OpenGL renderbuffer
	/// </summary>s
	class Renderbuffer {
		unsigned int id;

	public:
		inline unsigned int getId() { return id; }

		Renderbuffer() {
			glGenRenderbuffers(1, &id);
		}

		Renderbuffer& operator=(Renderbuffer& other) = delete;
		Renderbuffer(Renderbuffer& other) = delete;

		inline Renderbuffer& operator=(Renderbuffer&& other) noexcept {
			this->id = other.id;
			other.id = 0;
		};

		inline Renderbuffer(Renderbuffer&& other) noexcept {
			*this = std::forward<Renderbuffer>(other);
		};

		inline ~Renderbuffer() {
			glDeleteRenderbuffers(1, &id);
		}

		inline void bind() {
			glBindRenderbuffer(GL_RENDERBUFFER, id);
		}

		static inline void unbind() {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	};
}
