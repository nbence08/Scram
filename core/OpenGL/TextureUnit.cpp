#include "TextureUnit.h"

void TextureUnit::hollowBind() {
	if (activeTexUnit == unitNum) return;
	glActiveTexture(GL_TEXTURE0 + unitNum);
	
}

void TextureUnit::hollowUnbind() {
	if (activeTexUnit == unitNum) return;
	glActiveTexture(GL_TEXTURE0);
}

void TextureUnit::initTexture(const Texture2D& tex) {

	glTexParameteri(tex.type, GL_TEXTURE_MAG_FILTER, tex.magFilter);
	glTexParameteri(tex.type, GL_TEXTURE_MIN_FILTER, tex.minFilter);
	glTexParameteri(tex.type, GL_TEXTURE_WRAP_R, tex.wrapR);
	glTexParameteri(tex.type, GL_TEXTURE_WRAP_S, tex.wrapS);

}

TextureUnit::TextureUnit(int unitNum):unitNum(unitNum), boundTexture(nullptr) { }

std::shared_ptr<TextureUnit> TextureUnit::getNewInstance() {
	int minNum = 0;
	for (int i = 0; i <= textureUnits.size(); i++) {
		if (textureUnits.find(i) == textureUnits.end()) {
			minNum = i;
			break;
		}
		if (textureUnits[i].use_count() == 1 && textureUnits[i]->boundTexture.get() == nullptr) {
			return textureUnits[i];
		}
	}
	if (minNum == textureUnits.size()) {
		textureUnits.insert({minNum, std::shared_ptr<TextureUnit>(new TextureUnit(minNum))});
	}
	return textureUnits[minNum];
}

TextureUnit::~TextureUnit() {
	if(boundTexture.get() != nullptr) unbindTexture();
}

void TextureUnit::bind() {
	activeTexUnit = unitNum;
	glActiveTexture(GL_TEXTURE0 + unitNum);
	
}

void TextureUnit::unbind() {
	activeTexUnit = 0;
	glActiveTexture(GL_TEXTURE0);
}

void TextureUnit::bindTexture(std::shared_ptr<Texture2D> tex) {
	hollowBind();

	if (boundTexture.get() != nullptr) {
		boundTexture->setTextureUnit(nullptr);
	}
	boundTexture = tex;

	for (auto& pair : textureUnits) {
		if (pair.second.get() == this) {
			boundTexture->setTextureUnit(pair.second);
			break;
		}
	}

	glBindTexture(tex->type, tex->id);
	

	if (!tex->parametrized) {
		initTexture(*tex);
		tex->parametrized = true;
	}

	hollowUnbind();
}

void TextureUnit::unbindTexture() {
	if(boundTexture.get() == nullptr) return;
	hollowBind();

	glBindTexture(boundTexture->type, 0);

	boundTexture->textureUnit.reset();

	hollowUnbind();
}

void TextureUnit::loadTexture(const ImageData2D& d) {
	if (boundTexture.get() == nullptr) {
		throw std::runtime_error("Texture object is not bound");
	}
	hollowBind();
	glTexImage2D(boundTexture->type, 0, d.internalFormat, d.width, d.height, 0, d.format, d.type, d.pixels);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	
	hollowUnbind();
}