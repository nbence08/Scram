#include "TextureCube.h"

TextureCube::TextureCube(GLenum magFilter, GLenum minFilter,
	GLenum wrapR, GLenum wrapS, GLenum wrapT) {

	type = GL_TEXTURE_CUBE_MAP;

	//if type not in validTextureTypes, then reject

	this->minFilter = minFilter;
	this->magFilter = magFilter;
	this->wrapR = wrapR;
	this->wrapS = wrapS;
	this->wrapT = wrapT;

	glGenTextures(1, &id);

	parametrized = false;
}

TextureCube::~TextureCube() {
	glDeleteTextures(1, &id);
	if (!textureUnit.expired()) {
		auto texUSh = textureUnit.lock();
		texUSh->unbindTexture();
	}
}

bool TextureCube::isBoundToTextureUnit() {
	if (!this->textureUnit.expired()) {
		return textureUnit.lock()->doesBoundTextureMatch(this);
	}
	else return false;
}

int TextureCube::getTextureUnitNum() {
	if (textureUnit.expired()) {
		throw std::logic_error("No texture unit is set!");
	}
	auto texUSh = textureUnit.lock();
	return texUSh->getUnitNum();
}

void TextureCube::setTextureUnit(std::shared_ptr<TextureUnit> texUnit) {
	auto texUSh = textureUnit.lock();
	if (texUSh.get() != nullptr) {
		texUSh->unbindTexture();
	}
	textureUnit = texUnit;
}

void TextureCube::bindToNewTextureUnit(std::shared_ptr<TextureCube> self) {
	auto texUnit = TextureUnit::getNewInstance();
	texUnit->bindTexture(self);
}

void TextureCube::unsetTextureUnit() {
	textureUnit.reset();
}

void TextureCube::initialize() {

	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, wrapR);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapT);

}