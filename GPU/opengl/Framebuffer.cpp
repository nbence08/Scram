#include "Framebuffer.hpp"
#include "TextureUnit.hpp"
#include "Texture2D.hpp"
#include "TextureCube.hpp"

namespace ScOpenGL {

	Framebuffer::Framebuffer(unsigned int id) {
		if (id == 0) {
			this->id = id;
			hasColorBuffer = true;
			hasDepthBuffer = true;
			hasStencilBuffer = true;
			hasDepthStencilBuffer = true;
			frameWidth = global::screenWidth;
			frameHeight = global::screenHeight;
		}

		this->id = id;
		hasColorBuffer = false;
		hasDepthBuffer = false;
		hasStencilBuffer = false;
		hasDepthStencilBuffer = false;
		frameWidth = global::screenWidth;
		frameHeight = global::screenHeight;
	}

	Framebuffer::Framebuffer() {
		glGenFramebuffers(1, &id);
		frameHeight = frameWidth = 0;
		hasColorBuffer = false;
		hasDepthBuffer = false;
		hasStencilBuffer = false;
		hasDepthStencilBuffer = false;
	}

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
			createColorBuffer();
		}

		if (createInfo.depthStencilBuffer) {
			createDepthStencilBuffer();
		}
		if (createInfo.depthBuffer && !createInfo.depthStencilBuffer) {
			createDepthBuffer();
		}
		if (createInfo.stencilBuffer && !createInfo.depthStencilBuffer) {
			createStencilBuffer();
		}

		if (!createInfo.colorBuffer) {
			glNamedFramebufferDrawBuffer(id, GL_NONE);
			glNamedFramebufferReadBuffer(id, GL_NONE);
		}
		this->hasColorBuffer = createInfo.colorBuffer;
		this->hasDepthBuffer = createInfo.depthBuffer;
		this->hasStencilBuffer = createInfo.stencilBuffer;
		this->hasDepthStencilBuffer = createInfo.depthStencilBuffer;


		this->hollowUnbind();
	}

	Framebuffer::Framebuffer(FboCreateInfo createInfo) :Framebuffer(createInfo.width, createInfo.height, createInfo) {}

	void Framebuffer::createColorBuffer() {
		this->hollowBind();

		colorBuffer = std::make_shared<Texture2D>();
		auto texUnit = TextureUnit::getNewInstance();
		texUnit->bind();
		texUnit->bindTexture(colorBuffer);
		ImageData2D allocData;
		allocData.format = GL_RGBA;
		allocData.internalFormat = GL_RGBA;
		allocData.width = frameWidth;
		allocData.height = frameHeight;
		allocData.level = 0;
		allocData.type = GL_UNSIGNED_BYTE;
		allocData.pixels = nullptr;

		texUnit->loadTexture(allocData);


		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer->getId(), 0);
		hasColorBuffer = true;

		this->hollowUnbind();
		texUnit->unbindTexture();
		texUnit->unbind();
	}

	void Framebuffer::createDepthStencilBuffer() {
		this->hollowBind();

		ImageData2D dsInfo;
		dsInfo.format = GL_DEPTH_STENCIL;
		dsInfo.height = frameHeight;
		dsInfo.width = frameWidth;
		dsInfo.internalFormat = GL_DEPTH_STENCIL;
		dsInfo.level = 0;
		dsInfo.type = GL_UNSIGNED_BYTE;
		dsInfo.pixels = nullptr;

		dsBuffer = std::make_shared<Texture2D>();
		auto texUnit = TextureUnit::getNewInstance();
		texUnit->bind();
		texUnit->bindTexture(dsBuffer);
		texUnit->loadTexture(dsInfo);


		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, dsBuffer->getId(), 0);
		hasDepthStencilBuffer = true;

		texUnit->unbindTexture();
		texUnit->unbind();

		this->hollowUnbind();
	}

	void Framebuffer::createDepthBuffer() {
		this->hollowBind();

		colorBuffer = std::make_shared<Texture2D>();
		auto texUnit = TextureUnit::getNewInstance();
		texUnit->bind();
		texUnit->bindTexture(colorBuffer);

		ImageData2D allocData;
		allocData.format = GL_DEPTH_COMPONENT;
		allocData.internalFormat = GL_DEPTH_COMPONENT;
		allocData.width = frameWidth;
		allocData.height = frameHeight;
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

	void Framebuffer::createStencilBuffer() {
		this->hollowBind();

		colorBuffer = std::make_shared<Texture2D>();
		auto texUnit = TextureUnit::getNewInstance();
		texUnit->bind();
		texUnit->bindTexture(colorBuffer);
		ImageData2D allocData;
		allocData.format = GL_STENCIL_INDEX;
		allocData.internalFormat = GL_STENCIL_INDEX;
		allocData.width = frameWidth;
		allocData.height = frameHeight;
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


	void Framebuffer::setColorBuffer(std::shared_ptr<Texture2D> colorBuffer) {
		if (this->colorBuffer == colorBuffer) return;

		this->colorBuffer = colorBuffer;
		this->hasDepthBuffer = true;

		setAttachment(GL_COLOR_ATTACHMENT0, this->colorBuffer);
	}

	template <typename T>
	void Framebuffer::setDepthBuffer(std::shared_ptr<T> depthBuffer) {

		if (depthBufferEquals(depthBuffer)) return;

		this->depthBuffer = depthBuffer;
		this->hasDepthBuffer = true;

		setAttachment(GL_DEPTH_ATTACHMENT, depthBuffer);
	}
	template void Framebuffer::setDepthBuffer<Texture2D>(std::shared_ptr<Texture2D> depthBuffer);
	template void Framebuffer::setDepthBuffer<TextureCube>(std::shared_ptr<TextureCube> depthBuffer);

	//WARNING: non-DRY friendly code ahead
	void Framebuffer::setAttachment(GLenum attachmentType, std::shared_ptr<Texture2D> texture) {
		this->hollowBind();
		if (texture->isBoundToTextureUnit()) {
			auto texUnit = texture->getTextureUnit();
			texUnit->bind();

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, texture->getId(), 0);

			texUnit->unbind();
		}
		else {
			auto texUnit = TextureUnit::getNewInstance();
			texUnit->bind();
			texUnit->bindTexture(texture);

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, texture->getId(), 0);

			texUnit->unbindTexture();
			texUnit->unbind();
		}

		this->hollowUnbind();
	}
	void Framebuffer::setAttachment(GLenum attachmentType, std::shared_ptr<TextureCube> texture) {
		this->hollowBind();
		if (texture->isBoundToTextureUnit()) {
			auto texUnit = texture->getTextureUnit();
			texUnit->bind();


			glFramebufferTexture(GL_FRAMEBUFFER, attachmentType, texture->getId(), 0);


			texUnit->unbind();
		}
		else {
			auto texUnit = TextureUnit::getNewInstance();
			texUnit->bind();
			texUnit->bindTexture(texture);


			glFramebufferTexture(GL_FRAMEBUFFER, attachmentType, texture->getId(), 0);


			texUnit->unbindTexture();
			texUnit->unbind();
		}

		this->hollowUnbind();
	}
	//end of non-DRY friendly code

	void Framebuffer::setStencilBuffer(std::shared_ptr<Texture2D> stencilBuffer) {
		if (this->stencilBuffer == stencilBuffer) return;

		this->stencilBuffer = stencilBuffer;
		this->hasDepthBuffer = true;

		setAttachment(GL_STENCIL_ATTACHMENT, this->stencilBuffer);
	}

	unsigned int Framebuffer::getId() { return id; }

	Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept {
		if (this == &other) return *this;
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
		*this = std::forward<Framebuffer>(other);
	}

	Framebuffer::~Framebuffer() {
		if (boundFramebuffer == this->id) unbind();
		glDeleteFramebuffers(1, &id);
	}

	void Framebuffer::bind() {
		if (!hasColorBuffer && hasDepthBuffer) {
			glNamedFramebufferDrawBuffer(id, GL_NONE);
			glNamedFramebufferReadBuffer(id, GL_NONE);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, id);

		auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "framebuffer not complete" << std::endl;
			throw std::runtime_error("Framebuffer not complete!");
		}

		boundFramebuffer = this->id;
	}

	void Framebuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		boundFramebuffer = 0;
	}

}
