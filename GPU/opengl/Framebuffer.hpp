#pragma once
#pragma once
#include <memory>
#include <iostream>
#include <variant>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Global_Props.hpp"

#include "GPU_export.hpp"

namespace ScOpenGL {

class Texture2D;
class TextureCube;
class TextureCube;

	/// <summary>
	/// struct for signalling the Framebuffer constructor
	/// the types of buffers it should create, and the width, and height of those buffers
	/// multisampled versions are to be added later for antialiasing and different postprocessing methods
	/// </summary>
	struct GPU_EXPORT FboCreateInfo {
		bool colorBuffer;
		bool depthBuffer;
		bool stencilBuffer;
		bool depthStencilBuffer;
		int width, height;
	};

	class Framebuffer;
	static int boundFramebuffer;

	/// <summary>
	/// Framebuffer class which represents a framebuffer in OpenGL
	/// </summary>
	class GPU_EXPORT Framebuffer {
	private:

		unsigned int id;

		bool hasColorBuffer;
		std::shared_ptr<Texture2D> colorBuffer;

		bool hasDepthBuffer;
		std::variant<std::shared_ptr<Texture2D>, std::shared_ptr<TextureCube>> depthBuffer;

		bool hasStencilBuffer;
		std::shared_ptr<Texture2D> stencilBuffer;

		bool hasDepthStencilBuffer;
		std::shared_ptr<Texture2D> dsBuffer;

		int frameWidth;
		int frameHeight;


		void hollowBind();
		void hollowUnbind();
		void setAttachment(GLenum attachmentType, std::shared_ptr<Texture2D> texture);
		void setAttachment(GLenum attachmentType, std::shared_ptr<TextureCube> texture);

		Framebuffer(unsigned int id);
	public:

		Framebuffer();

		static inline Framebuffer getDefault() {
			return Framebuffer(0);
		}

		Framebuffer(Framebuffer&& other) noexcept;
		~Framebuffer();
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;
		Framebuffer(int width, int height, FboCreateInfo createInfo);
		Framebuffer(FboCreateInfo createInfo);

		void createColorBuffer();
		void createDepthStencilBuffer();
		void createDepthBuffer();
		void createStencilBuffer();


		void setColorBuffer(std::shared_ptr<Texture2D> colorBuffer);
		void setStencilBuffer(std::shared_ptr<Texture2D> stencilBuffer);

		unsigned int getId();

		template <typename T>
		inline std::shared_ptr<T> getDepthBuffer() { return std::get<std::shared_ptr<T>>(depthBuffer); }

		template <typename T>
		inline bool depthBufferEquals(std::shared_ptr<T> val) {
			if (!hasDepthBuffer) return false;
			return static_cast<void*>(val.get()) == std::visit([](auto& depthBuffer) { return static_cast<void*>(depthBuffer.get()); }, depthBuffer);
		}

		template <typename T>
		void setDepthBuffer(std::shared_ptr<T> depthBuffer) {

			if (depthBufferEquals(depthBuffer)) return;

			this->depthBuffer = depthBuffer;
			this->hasDepthBuffer = true;

			setAttachment(GL_DEPTH_ATTACHMENT, depthBuffer);
		}

		Framebuffer& operator=(Framebuffer&& other) noexcept;

		void bind();

		static void unbind();
	};
}
