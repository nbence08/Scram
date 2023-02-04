#pragma once
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <stack>
#include <variant>

#include "Texture2D.hpp"
#include "TextureCube.hpp"
#include "core/Struct_Definitions.hpp"

class Texture2D;
class TextureCube;

class TextureUnit;

static std::unordered_map<int, std::shared_ptr<TextureUnit>> textureUnits;
static std::shared_ptr<std::stack<int>> bindStack = std::make_shared<std::stack<int>>();
static int activeTexUnit = 0;

/// <summary>
/// Class representing an OpenGL texture unit 
/// </summary>
class TextureUnit{
private:
	unsigned int unitNum;
	
	std::variant<std::shared_ptr<Texture2D>, std::shared_ptr<TextureCube>> boundTexture;

	void hollowBind();
	void hollowUnbind();
	void initTexture(const Texture2D& tex);
	TextureUnit(int unitNum);

	friend class Texture2D;
public:
	
	TextureUnit(const TextureUnit& other) = delete;
	TextureUnit& operator=(const TextureUnit& other) = delete;
	~TextureUnit();
	static std::shared_ptr<TextureUnit> getNewInstance();

	void bind();
	static void unbind();

	template <typename T>
	void bindTexture(std::shared_ptr<T> tex);
	void unbindTexture();
	void loadTexture(const ImageData2D& d);
	void loadTexture(const ImageDataCube& d);

	inline int getUnitNum() const {return unitNum;}

	template <typename T>
	inline bool doesBoundTextureMatch(T* tex){

		return static_cast<void*>(tex) == std::visit([](auto& boundTex){ return static_cast<void*>(boundTex.get());}, boundTexture);
		//auto texPtr = std::get<std::shared_ptr<Texture2D>>(boundTexture);

	}
	/*
	inline bool doesBoundTextureMatch(TextureCube* tex) {
		if (boundTexture.index() == 1) {
			auto texPtr = std::get<std::shared_ptr<TextureCube>>(boundTexture);
			return texPtr.get() == tex;
		}
		return false;
	}
	*/
	inline bool hasBoundTexture() {
		return !boundTexture.valueless_by_exception();
	}

	bool isBoundTextureEmpty();
};
