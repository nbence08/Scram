#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "ConstantHolder.h"
#include <iostream>

class Texture{};

class Texture2D {
public:
	unsigned int id;
};

class MultisampledTexture2D {
public:
	unsigned int id;
};

class Renderbuffer {
public:
	unsigned int id;
};

class MultisampledRenderbuffer {
public:
	unsigned int id;
};

class Framebuffer{
private:
	unsigned int id;

	Texture2D colorBuffer;
	MultisampledTexture2D multisampledColorbuffer;

	Texture depthBuffer;
	Texture stencilBuffer;
	MultisampledRenderbuffer multisampledDepthStencilBuffer;

	bool finished;

	int frameWidth;
	int frameHeight;

	static std::shared_ptr<Framebuffer> defaultFbo;
	static Framebuffer* boundFramebuffer;

	void hollowBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void hollowUnbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, boundFramebuffer->id);
	}

public:
	Framebuffer(int frameWidth = 800, int frameHeight = 800):frameWidth(frameWidth), frameHeight(frameHeight) {
		unsigned int fbo;
		glGenFramebuffers(1, &id);
		finished = false;


	}
	Framebuffer(unsigned int id) :id(id) {}

	Framebuffer& setSize(int frameWidth, int frameHeight) {
		this->frameWidth = frameWidth;
		this->frameHeight = frameHeight;
	}

	//set a multisampled 2D texture as a colorbuffer
	Framebuffer& setMSColorBufTex() {
		glGenTextures(1, &multisampledColorbuffer.id);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multisampledColorbuffer.id);

		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, ConstantHolder::samples, GL_RGBA, (int)frameWidth, (int)frameHeight, GL_TRUE);
		hollowBind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multisampledColorbuffer.id, 0);
		hollowUnbind();
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		return *this;
	}

	//set a mulstisampled 2D renderbuffer as merged depth/stencil buffer
	Framebuffer& setMSDphStcBufRenBuf() {
		glGenRenderbuffers(1, &multisampledDepthStencilBuffer.id);
		glBindRenderbuffer(GL_RENDERBUFFER, multisampledDepthStencilBuffer.id);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, ConstantHolder::samples, GL_DEPTH24_STENCIL8, frameWidth, frameHeight);
		
		hollowBind();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, multisampledDepthStencilBuffer.id);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		hollowUnbind();
		return *this;
	}

	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		if (!finished) {
			auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
				std::cout << "framebuffer not complete" << std::endl;
				throw std::exception("Framebuffer not complete!");
			}
			finished = true;
		}
		boundFramebuffer = this;
	}

	static void bindDefault() {
		defaultFbo->bind();
	}
};

std::shared_ptr<Framebuffer> Framebuffer::defaultFbo = std::make_shared<Framebuffer>(0);
Framebuffer* Framebuffer::boundFramebuffer = Framebuffer::defaultFbo.get();
