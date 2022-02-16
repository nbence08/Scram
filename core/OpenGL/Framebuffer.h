#pragma once
#pragma once
#include <memory>
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "core/Global_Props.hpp"
#include "Texture2D.h"


/// <summary>
/// struct for signalling the Framebuffer constructor
/// the types of buffers it should create, and the width, and height of those buffers
/// multisampled versions are to be added later for antialiasing and different postprocessing methods
/// </summary>
struct FboCreateInfo {
	bool colorBuffer;
	bool depthBuffer;
	bool stencilBuffer;
	bool depthStencilBuffer;
	int width, height;
};

class Framebuffer;
static int boundFramebuffer;

class Framebuffer {
private:

	unsigned int id;

	bool hasColorBuffer;
	std::shared_ptr<Texture2D> colorBuffer;

	bool hasDepthBuffer;
	std::variant<std::shared_ptr<Texture2D>, std::shared_ptr<TextureCube>> depthBuffer;

	bool hasStencilBuffer;
	std::shared_ptr<Texture2D> stencilBuffer;

	bool hasDepthStencilBuffer;

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
	void createDepthBuffer();
	void createStencilBuffer();


	void setColorBuffer(std::shared_ptr<Texture2D> colorBuffer);
	void setStencilBuffer(std::shared_ptr<Texture2D> stencilBuffer);

	inline unsigned int getId() { return id; }

	template <typename T>
	inline std::shared_ptr<T> getDepthBuffer(){ return std::get<std::shared_ptr<T>>(depthBuffer); }

	template <typename T>
	inline bool depthBufferEquals(std::shared_ptr<T> val) {
		if(!hasDepthBuffer) return false;
		return static_cast<void*>(val.get()) ==  std::visit([](auto& depthBuffer) { return static_cast<void*>(depthBuffer.get()); }, depthBuffer);
	}

	template <typename T>
	void setDepthBuffer(std::shared_ptr<T> depthBuffer);

	Framebuffer& operator=(Framebuffer&& other) noexcept;

	void bind();

	static void unbind();
};