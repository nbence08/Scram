#include "Texture2D.h"

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

int Texture2D::getTextureUnitNum() {
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