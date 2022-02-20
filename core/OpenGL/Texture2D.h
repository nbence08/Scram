#pragma once

#include <set>
#include <memory>

#include "GL/glew.h"
#include "TextureUnit.h"

/*static const std::set<GLenum> validTextureTypes = {
	 GL_TEXTURE_1D,
	 GL_TEXTURE_2D,
	 GL_TEXTURE_3D,
	 GL_TEXTURE_1D_ARRAY,
	 GL_TEXTURE_2D_ARRAY,
	 GL_TEXTURE_RECTANGLE,
	 GL_TEXTURE_CUBE_MAP,
	 GL_TEXTURE_CUBE_MAP_ARRAY,
	 GL_TEXTURE_BUFFER,
	 GL_TEXTURE_2D_MULTISAMPLE, 
	 GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};*/

class TextureUnit;

/// <summary>
/// class representing a 2D texture in OpenGL
/// </summary>
class Texture2D {
	unsigned int id;
	std::weak_ptr<TextureUnit> textureUnit;

	GLenum type;
	GLenum minFilter, magFilter;
	GLenum wrapS, wrapR;

	bool parametrized;

	friend class TextureUnit;
public:

	Texture2D(GLenum magFilter = GL_LINEAR, GLenum minFilter = GL_LINEAR,
			  GLenum wrapR = GL_REPEAT, GLenum wrapS = GL_REPEAT);

	int getTextureUnitNum();
	void setTextureUnit(std::shared_ptr<TextureUnit> texUnit);
	static void bindToNewTextureUnit(std::shared_ptr<Texture2D> self);
	inline std::shared_ptr<TextureUnit> getTextureUnit(){ return textureUnit.lock(); }
	void unsetTextureUnit();
	unsigned int getId() { return id; }
	void initialize();

	~Texture2D();
	bool isBoundToTextureUnit();
};

