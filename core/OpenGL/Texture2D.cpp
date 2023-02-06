#include "Texture2D.hpp"

namespace ScOpenGL {
	Texture2D::Texture2D(GLenum magFilter, GLenum minFilter,
		GLenum wrapR, GLenum wrapS) {

		type = GL_TEXTURE_2D;

		//if type not in validTextureTypes, then reject

		this->minFilter = minFilter;
		this->magFilter = magFilter;
		this->wrapR = wrapR;
		this->wrapS = wrapS;

		glGenTextures(1, &id);

		parametrized = false;
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &id);
		if (!textureUnit.expired()) {
			auto texUSh = textureUnit.lock();
			texUSh->unbindTexture();
		}
	}

	bool Texture2D::isBoundToTextureUnit() {
		if (!this->textureUnit.expired()) {
			return this->textureUnit.lock()->doesBoundTextureMatch(this);
		}
		else return false;
	}

	int Texture2D::getTextureUnitNum() {
		if (textureUnit.expired()) {
			throw std::logic_error("No texture unit is set!");
		}
		auto texUSh = textureUnit.lock();
		return texUSh->getUnitNum();
	}

	void Texture2D::setTextureUnit(std::shared_ptr<TextureUnit> texUnit) {
		auto texUSh = textureUnit.lock();
		if (texUSh.get() != nullptr) {
			texUSh->unbindTexture();
		}
		textureUnit = texUnit;
	}

	void Texture2D::bindToNewTextureUnit(std::shared_ptr<Texture2D> self) {
		auto texUnit = TextureUnit::getNewInstance();
		texUnit->bindTexture(self);
	}

	void Texture2D::unsetTextureUnit() {
		textureUnit.reset();
	}

	void Texture2D::initialize() {

		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(type, GL_TEXTURE_WRAP_R, wrapR);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);

	}
}
