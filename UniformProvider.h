#pragma once

#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformProvider{

private:
	unsigned int program;
	std::unordered_map<std::string, GLint> cache;

public:
	inline UniformProvider(): program(0) {};
	inline UniformProvider(unsigned int program): program(program){}

	inline void setProgram(unsigned int program){ this->program = program; }

	inline void uniform(std::string name, float value) {
		GLint location = getUniformLocation(name);
		glProgramUniform1f(program, location, value);
	}

	inline void uniform(std::string name, int value) {
		GLint location = getUniformLocation(name);
		glProgramUniform1i(program, location, value);
	}

	inline void uniform(std::string name, glm::vec2 value) {
		GLint location = getUniformLocation(name);
		glProgramUniform2fv(program, location, 1, glm::value_ptr(value));
	}

	inline void uniform(std::string name, glm::vec3 value) {
		GLint location = getUniformLocation(name);
		glProgramUniform3fv(program, location, 1, glm::value_ptr(value));
	}

	inline void uniform(std::string name, glm::vec4 value) {
		GLint location = getUniformLocation(name);
		glProgramUniform4fv(program, location, 1, glm::value_ptr(value));
	}

	inline void uniform(std::string name, glm::mat4 value) {
		GLint location = getUniformLocation(name);
		glProgramUniformMatrix4fv(program, location, 1, GL_FALSE, &value[0][0]);
	}

	inline GLint getUniformLocation(std::string name) {
		GLint location;
		if (cache.find(name) == cache.end()) {
			location = glGetUniformLocation(program, name.c_str());
			cache[name] = location;
		}
		else location = cache[name];
		return location;
	}
};

