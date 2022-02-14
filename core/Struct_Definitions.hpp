#pragma once

#include "GL/glew.h"

struct ImageData2D {
	GLint level;
	GLint internalFormat;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	void* pixels;
};

struct ImageDataCube {
	GLint level;
	GLint internalFormat;
	GLsizei size;
	GLenum format;
	GLenum type;

	/*void* posX;
	void* negX;
	void* posY;
	void* negY;
	void* posZ;
	void* negZ;*/
	void* pixels[6];
};
