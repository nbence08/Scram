#pragma once
#include <memory>

#include "GL/glew.h"

class TextureUnit;

/// <summary>
/// class representing a cube texture in OpenGL
/// </summary>
class TextureCube {
	unsigned int id;
	std::weak_ptr<TextureUnit> textureUnit;

	GLenum type;
	GLenum minFilter, magFilter;
	GLenum wrapS, wrapR, wrapT;

	bool parametrized;

	friend class TextureUnit;
public:

	TextureCube(GLenum magFilter = GL_NEAREST, GLenum minFilter = GL_NEAREST,
		GLenum wrapR = GL_CLAMP_TO_EDGE, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);

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