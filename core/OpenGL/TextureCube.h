#pragma once
#include <memory>

#include "GL/glew.h"
#include "TextureUnit.h"

class TextureUnit;

class TextureCube {
	unsigned int id;
	std::weak_ptr<TextureUnit> textureUnit;

	GLenum type;
	GLenum minFilter, magFilter;
	GLenum wrapS, wrapR, wrapT;

	bool parametrized;

	friend class TextureUnit;
public:

	TextureCube(GLenum magFilter = GL_LINEAR, GLenum minFilter = GL_LINEAR,
		GLenum wrapR = GL_REPEAT, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT);

	int getTextureUnitNum();
	void setTextureUnit(std::shared_ptr<TextureUnit> texUnit);
	static void bindToNewTextureUnit(std::shared_ptr<TextureCube> self);
	inline std::shared_ptr<TextureUnit> getTextureUnit() { return textureUnit.lock(); }
	void unsetTextureUnit();
	void initialize();
	unsigned int getId() { return id; }

	~TextureCube();
	bool isBoundToTextureUnit();
};