#include "Framebuffer.h"

void Framebuffer::hollowBind() {
	if (boundFramebuffer == this->id) return;
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::hollowUnbind() {
	if (boundFramebuffer == this->id) return;
	glBindFramebuffer(GL_FRAMEBUFFER, boundFramebuffer);
}

Framebuffer::Framebuffer(int width, int height, FboCreateInfo createInfo) : frameWidth(width), frameHeight(height) {
	glGenFramebuffers(1, &id);
	this->hollowBind();
	if (createInfo.colorBuffer) {
		createColorBuffer(width, height);
	}

	if (createInfo.depthStencilBuffer) {
		//create joint depth-stencil buffer
		//TODO: implement it
	}
	if (createInfo.depthBuffer && !createInfo.depthStencilBuffer) {
		createDepthBuffer(width, height);
	}
	if (createInfo.stencilBuffer && !createInfo.depthStencilBuffer) {
		createStencilBuffer(width, height);
	}

	if (!createInfo.colorBuffer) {
		glNamedFramebufferDrawBuffer(id, GL_NONE);
		glNamedFramebufferReadBuffer(id, GL_NONE);
	}

	this->hollowUnbind();
}

void Framebuffer::createColorBuffer(int width, int height) {
	colorBuffer = std::make_shared<Texture2D>();
	auto texUnit = TextureUnit::getNewInstance();
	texUnit->bind();
	texUnit->bindTexture(colorBuffer);
	ImageData2D allocData;
	allocData.format = GL_RGBA;
	allocData.internalFormat = GL_RGBA;
	allocData.width = width;
	allocData.height = height;
	allocData.level = 0;
	allocData.type = GL_UNSIGNED_BYTE;
	allocData.pixels = nullptr;

	texUnit->loadTexture(allocData);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer->getId(), 0);
	hasColorBuffer = true;

	this->hollowUnbind();
	texUnit->unbindTexture();
}

void Framebuffer::createDepthBuffer(int width, int height) {
	this->hollowBind();

	colorBuffer = std::make_shared<Texture2D>();
	auto texUnit = TextureUnit::getNewInstance();
	texUnit->bind();
	texUnit->bindTexture(colorBuffer);
	ImageData2D allocData;
	allocData.format = GL_DEPTH_COMPONENT;
	allocData.internalFormat = GL_DEPTH_COMPONENT;
	allocData.width = width;
	allocData.height = height;
	allocData.level = 0;
	allocData.type = GL_UNSIGNED_BYTE;
	allocData.pixels = nullptr;

	texUnit->loadTexture(allocData);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, colorBuffer->getId(), 0);
	hasDepthBuffer = true;

	texUnit->unbindTexture();
	texUnit->unbind();
	this->hollowUnbind();
}

void Framebuffer::createStencilBuffer(int width, int height) {
	this->hollowBind();

	colorBuffer = std::make_shared<Texture2D>();
	auto texUnit = TextureUnit::getNewInstance();
	texUnit->bind();
	texUnit->bindTexture(colorBuffer);
	ImageData2D allocData;
	allocData.format = GL_STENCIL_INDEX;
	allocData.internalFormat = GL_STENCIL_INDEX;
	allocData.width = width;
	allocData.height = height;
	allocData.level = 0;
	allocData.type = GL_UNSIGNED_BYTE;
	allocData.pixels = nullptr;

	texUnit->loadTexture(allocData);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, colorBuffer->getId(), 0);
	hasStencilBuffer = true;
	texUnit->unbindTexture();
	texUnit->unbind();
	this->hollowUnbind();
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
	this->colorBuffer = other.colorBuffer;
	this->depthBuffer = other.depthBuffer;
	this->stencilBuffer = other.stencilBuffer;

	this->hasDepthBuffer = other.hasDepthBuffer;
	this->hasStencilBuffer = other.hasStencilBuffer;
	this->hasColorBuffer = other.hasColorBuffer;
	this->hasDepthStencilBuffer = other.hasDepthStencilBuffer;

	this->frameHeight = other.frameHeight;
	this->frameWidth = other.frameWidth;

	this->id = other.id;
	other.id = 0;
	return *this;
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept {
	*this = std::move(other);
}

Framebuffer::~Framebuffer() {
	if (boundFramebuffer == this->id) unbind();
	glDeleteFramebuffers(1, &id);
}

void Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	if (!hasColorBuffer && hasDepthBuffer) {
		glNamedFramebufferDrawBuffer(id, GL_NONE);
		glNamedFramebufferReadBuffer(id, GL_NONE);
	}

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "framebuffer not complete" << std::endl;
		throw std::exception("Framebuffer not complete!");
	}

	boundFramebuffer = this->id;
}

void Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	boundFramebuffer = 0;
}

/*Framebuffer& setSize(int frameWidth, int frameHeight) {
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
}*/

//set a multisampled 2D texture as a colorbuffer
/*Framebuffer& setMSColorBufTex() {
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
}*/