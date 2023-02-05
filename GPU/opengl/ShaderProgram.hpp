#pragma once
#include "GL/glew.h"
#include <string>
#include <stdexcept>
#include "UniformProvider.hpp"

static unsigned int programInUse = 0;

/// <summary>
/// Class representing an OpenGL shader program
/// One has to link the program manually in order to be able to use it
/// </summary>
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

	ShaderProgram(ShaderProgram&& other) noexcept;

	ShaderProgram& operator=(ShaderProgram&& other) noexcept;


	void addFragment(const char** source);

	void addVertex(const char** source);

	void addGeometry(const char** source);

	void linkProgram();

	void use();

	unsigned int getId() const;

	/// <summary>
	/// Variadic function which invokes the proper overload
	/// of setUniform of the class' UniformProvider object
	/// </summary>
	/// <typeparam name="...T"></typeparam>
	/// <param name="name">name of the uniform</param>
	/// <param name="...t">params to be set</param>
	template <typename... T>
	void inline setUniform(std::string name, T... t) {
		up.setUniform(name, t...);
	}

	/// <summary>
	/// Variadic function which invokes the proper overload
	/// of setUniform of the class' UniformProvider object	/// </summary>
	/// <typeparam name="...T"></typeparam>
	/// <param name="...t"></param>
	template <typename... T>
	void inline setUniform(T... t) {
		up.setUniform(t...);
	}

	UniformProvider& getUniformProvider() { return up; }
};

