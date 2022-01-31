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
