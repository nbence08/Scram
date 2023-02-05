#include "TextureUnit.hpp"
#include "Texture2D.hpp"
#include "TextureCube.hpp"

static std::unordered_map<int, std::shared_ptr<TextureUnit>> textureUnits;
static std::shared_ptr<std::stack<int>> bindStack = std::make_shared<std::stack<int>>();
static int activeTexUnit = 0;

void clearTextureUnits() {
	textureUnits.clear();
}

void TextureUnit::hollowBind() {
	if(bindStack->size() == 0 && activeTexUnit == unitNum) return;
	bindStack->push(unitNum);
	glActiveTexture(GL_TEXTURE0 + unitNum);
	
}

void TextureUnit::hollowUnbind() {
	if(bindStack->size() == 0 && activeTexUnit == unitNum) return;
	if (bindStack->top() != unitNum){
		throw std::logic_error("Trying to hollow unbind, but other unit is bound.");
	}
	bindStack->pop();
	if (bindStack->size() == 0) {
		glActiveTexture(GL_TEXTURE0 + activeTexUnit);
	}
	else {
		glActiveTexture(GL_TEXTURE0 + bindStack->top());
	}
}

void TextureUnit::initTexture(const Texture2D& tex) {

	glTexParameteri(tex.type, GL_TEXTURE_MAG_FILTER, tex.magFilter);
	glTexParameteri(tex.type, GL_TEXTURE_MIN_FILTER, tex.minFilter);
	glTexParameteri(tex.type, GL_TEXTURE_WRAP_R, tex.wrapR);
	glTexParameteri(tex.type, GL_TEXTURE_WRAP_S, tex.wrapS);

}

TextureUnit::TextureUnit(int unitNum):unitNum(unitNum) {}

std::shared_ptr<TextureUnit> TextureUnit::getNewInstance() {
	int minNum = 0;
	for (int i = 0; i <= textureUnits.size(); i++) {
		if (textureUnits.find(i) == textureUnits.end()) {
			minNum = i;
			break;
		}
		if (textureUnits[i].use_count() == 1 && !textureUnits[i]->hasBoundTexture()) {
			return textureUnits[i];
		}
	}
	if (minNum == textureUnits.size()) {
		textureUnits.insert({minNum, std::shared_ptr<TextureUnit>(new TextureUnit(minNum))});
	}
	return textureUnits[minNum];
}

TextureUnit::~TextureUnit() {}

void TextureUnit::bind() {
	activeTexUnit = unitNum;
	glActiveTexture(GL_TEXTURE0 + unitNum);
	
}

void TextureUnit::unbind() {
	activeTexUnit = 0;
	glActiveTexture(GL_TEXTURE0);
}

template<typename T>
void TextureUnit::bindTexture(std::shared_ptr<T> tex) {
	hollowBind();

	if(!isBoundTextureEmpty()){
	//if (boundTexture.get() != nullptr) {
		if(doesBoundTextureMatch(tex.get())) return;

		std::visit([](auto& arg){ arg->unsetTextureUnit(); }, boundTexture);
	}
	boundTexture = tex;

	for (auto& pair : textureUnits) {
		if (pair.second.get() == this) {
			std::visit([&pair](auto& tex){ tex->setTextureUnit(pair.second); }, boundTexture);
			break;
		}
	}

	glBindTexture(tex->type, tex->id);
	
	std::visit([](auto& tex) {
		if (!tex->parametrized) {
			tex->initialize();
			tex->parametrized = true;
		}
	}, boundTexture);


	hollowUnbind();
}
template void TextureUnit::bindTexture<Texture2D>(std::shared_ptr<Texture2D> tex);
template void TextureUnit::bindTexture<TextureCube>(std::shared_ptr<TextureCube> tex);

void TextureUnit::unbindTexture() {
	if(isBoundTextureEmpty()) return;

	glBindTextureUnit(this->unitNum, 0);

	std::visit([](auto& tex){ tex.reset();}, boundTexture);
}

void TextureUnit::loadTexture(const ImageData2D& d) {
	try {
		std::shared_ptr<Texture2D> tex = std::get<std::shared_ptr<Texture2D>>(boundTexture);
		hollowBind();

		glTexImage2D(tex->type, 0, d.internalFormat, d.width, d.height, 0, d.format, d.type, d.pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	
		hollowUnbind();
	}
	catch (std::bad_variant_access e) {
		throw std::runtime_error("Texture2D object is not bound.");
	}
}


void TextureUnit::loadTexture(const ImageDataCube& d) {
	try {
		std::shared_ptr<TextureCube> tex = std::get<std::shared_ptr<TextureCube>>(boundTexture);
		hollowBind();

		bool null = false;
		for (int i = 0; i < 6; i++) {
			if(d.pixels[i] == nullptr) null = true;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, d.level, d.internalFormat, d.size, d.size, 0, d.format, d.type, d.pixels[i]);
		}

		if (!null) glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		hollowUnbind();
	}
	catch (std::bad_variant_access e) {
		throw std::runtime_error("TextureCube object is not bound.");
	}
}

int TextureUnit::getUnitNum() const { return unitNum; }

bool TextureUnit::isBoundTextureEmpty() {
	if (boundTexture.valueless_by_exception()) return true;
	return std::visit([](auto& arg){ return arg.get() == nullptr;}, boundTexture);
}

bool TextureUnit::hasBoundTexture() {
	return !boundTexture.valueless_by_exception();
}

template <typename T>
bool TextureUnit::doesBoundTextureMatch(T* tex) {
	return static_cast<void*>(tex) == std::visit([](auto& boundTex) { return static_cast<void*>(boundTex.get()); }, boundTexture);
}
