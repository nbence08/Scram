#pragma once
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <memory>

#include "Texture2D.h"
#include "core/Struct_Definitions.hpp"

class Texture2D;

class TextureUnit;

static std::unordered_map<int, std::shared_ptr<TextureUnit>> textureUnits;
static int activeTexUnit = 0;

class TextureUnit{
private:
	unsigned int unitNum;
	std::shared_ptr<Texture2D> boundTexture;

	void hollowBind();

	void hollowUnbind();

	void initTexture(const Texture2D& tex);

	TextureUnit(int unitNum);

	bool deleted;
public:
	
	TextureUnit(const TextureUnit& other) = delete;

	TextureUnit& operator=(const TextureUnit& other) = delete;

	~TextureUnit();

	static std::shared_ptr<TextureUnit> getNewInstance();

	void bind();

	static void unbind();

	void bindTexture(std::shared_ptr<Texture2D> tex);

	void unbindTexture();

	void loadTexture(const ImageData2D& d);

	inline int getUnitNum() const {return unitNum;}
};
