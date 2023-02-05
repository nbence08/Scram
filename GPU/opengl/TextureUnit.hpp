#pragma once
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <stack>
#include <variant>

#include "Struct_Definitions.hpp"

class Texture2D;
class TextureCube;
class TextureUnit;

void clearTextureUnits();

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
	bool doesBoundTextureMatch(T* tex);
	bool hasBoundTexture();
	bool isBoundTextureEmpty();
};
