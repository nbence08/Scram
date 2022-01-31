#pragma once
#include "GL/glew.h"
#include <string>
#include <stdexcept>
#include "UniformProvider.h"

static unsigned int programInUse = 0;

class ShaderProgram {
	
	unsigned id;
	void checkShaderErorrs(unsigned int id);
	UniformProvider up;
public:
	ShaderProgram();
	~ShaderProgram();

	void addFragment(const char** source);

	void addVertex(const char** source);

	void linkProgram();

	void use();

	inline unsigned int getId() const {
		return id;
	}

	UniformProvider& getUniformProvider() { return up; }
};

