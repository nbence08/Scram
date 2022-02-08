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

	void addShader(const char** source, GLenum shaderType);
public:
	ShaderProgram();
	~ShaderProgram();

	ShaderProgram(const ShaderProgram&) = delete;

	ShaderProgram& operator=(const ShaderProgram&) = delete;

	ShaderProgram(ShaderProgram&& other) noexcept {
		*this = std::forward<ShaderProgram>(other);
	}

	ShaderProgram& operator=(ShaderProgram&& other) noexcept {
		if(this == &other) return *this;

		id = other.id;
		other.id = 0;


		return *this;
	}


	void addFragment(const char** source);

	void addVertex(const char** source);

	void addGeometry(const char** source);

	void linkProgram();

	void use();

	inline unsigned int getId() const {
		return id;
	}

	UniformProvider& getUniformProvider() { return up; }
};

