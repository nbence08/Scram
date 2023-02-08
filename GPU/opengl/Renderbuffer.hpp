#include <type_traits>
#include "GL/glew.h"

namespace ScOpenGL {

	/// <summary>
	/// class representing an OpenGL renderbuffer
	/// </summary>s
	class Renderbuffer {
		unsigned int id;

	public:
		unsigned int getId();

		Renderbuffer();

		Renderbuffer& operator=(Renderbuffer& other) = delete;
		Renderbuffer(Renderbuffer& other) = delete;

		Renderbuffer& operator=(Renderbuffer&& other) noexcept;

		Renderbuffer(Renderbuffer&& other) noexcept;

		~Renderbuffer();

		void bind();

		static void unbind();
	};

}
