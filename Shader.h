#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "UniformProvider.h"

class Shader{
private:
	std::string vtxPath;
	std::string fgPath;
	std::string geomPath;
	unsigned int program;
	UniformProvider uprovider;

public:
	Shader() = delete;
	Shader(std::string vtxPath, std::string fgPath, std::string geomPath = "");

public:	inline void use() {
		glUseProgram(program);
	}

public:	inline unsigned int id() const { return program; }

public: inline UniformProvider& uniforms() { return uprovider; }

private: unsigned int createShader(std::string& source, GLenum shaderType);

private: inline std::string loadFile(std::string path) {
		std::ifstream fileStream(path, std::ifstream::in);
		std::stringstream fileStringStream;
		fileStringStream << fileStream.rdbuf();
		return fileStringStream.str();
	}
};

