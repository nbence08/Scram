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
	std::shared_ptr<Texture2D> depthBuffer;

	bool hasStencilBuffer;
	std::shared_ptr<Texture2D> stencilBuffer;

	bool hasDepthStencilBuffer;

	int frameWidth;
	int frameHeight;


	void hollowBind();

	void hollowUnbind();

	void setAttachment(GLenum bufferType, std::shared_ptr<Texture2D> texture);

	inline Framebuffer(unsigned int id) {
		if (id == 0) {
			this->id = id;
			hasColorBuffer = true;
			hasDepthBuffer = true;
			hasStencilBuffer = true;
			hasDepthStencilBuffer = true;
			frameWidth = global::screenWidth;
			frameHeight = global::screenHeight;
		}

		this->id = false;
		hasColorBuffer = false;
		hasDepthBuffer = false;
		hasStencilBuffer = false;
		hasDepthStencilBuffer = false;
		frameWidth = global::screenWidth;
		frameHeight = global::screenHeight;
	}
public:
	
	inline Framebuffer() {
		glGenFramebuffers(1, &id);
		frameHeight = frameWidth = 0;
		hasColorBuffer = false;
		hasDepthBuffer = false;
		hasStencilBuffer = false;
		hasDepthStencilBuffer = false;
	}

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
	void setDepthBuffer(std::shared_ptr<Texture2D> depthBuffer);
	void setStencilBuffer(std::shared_ptr<Texture2D> stencilBuffer);

	inline unsigned int getId() { return id; }

	inline std::shared_ptr<Texture2D>& getDepthBuffer(){ return depthBuffer; }

	Framebuffer& operator=(Framebuffer&& other) noexcept;

	void bind();

	static void unbind();
};