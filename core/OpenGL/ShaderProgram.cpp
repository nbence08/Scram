#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
	id = glCreateProgram();
	if (id == 0) {
		throw std::runtime_error("glCreateProgram return 0");
	}
	up = UniformProvider(id);
}


void ShaderProgram::addFragment(const char** source) {
	unsigned int fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, source, nullptr);
	glCompileShader(fragId);

	checkShaderErorrs(fragId);

	glAttachShader(id, fragId);

	glDeleteShader(fragId);
}

void ShaderProgram::addVertex(const char** source) {
	unsigned int vertId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertId, 1, source, nullptr);
	glCompileShader(vertId);

	checkShaderErorrs(vertId);

	glAttachShader(id, vertId);

	glDeleteShader(vertId);
}

void ShaderProgram::linkProgram() {
	glLinkProgram(id);
	glValidateProgram(id);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		int infoLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLength);
		std::string log;
		log.resize((int64_t)(infoLength) + 1);
		char* logPtr = const_cast<char*>(log.data());

		glGetProgramInfoLog(id, infoLength, NULL, logPtr);
		throw std::runtime_error(log);
	}
}

void ShaderProgram::use() {
	glUseProgram(id);
	programInUse = id;
}

ShaderProgram::~ShaderProgram() {
	if (programInUse == id) {
		glUseProgram(0);
	}
	glDeleteProgram(id);
}

void ShaderProgram::checkShaderErorrs(unsigned int id) {
	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		int infoLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLength);
		std::string log;
		log.resize((int64_t)(infoLength)+ 1);
		char* logPtr = const_cast<char*>(log.data());

		glGetShaderInfoLog(id, infoLength, NULL, logPtr);
		throw std::runtime_error(log);
	}
}