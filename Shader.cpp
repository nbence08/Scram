#include "Shader.h"

Shader::Shader(std::string vtxPath, std::string fgPath, std::string geomPath) :
	vtxPath(vtxPath),
	fgPath(fgPath),
	geomPath(geomPath) {
	std::string vtx = loadFile(vtxPath);
	std::string fg = loadFile(fgPath);

	program = glCreateProgram();
	unsigned int vtxId = createShader(vtx, GL_VERTEX_SHADER);
	unsigned int fgId = createShader(fg, GL_FRAGMENT_SHADER);
	unsigned int geomId;
	glAttachShader(program, vtxId);
	glAttachShader(program, fgId);

	if (geomPath.length() > 0) {
		std::string geom = loadFile(geomPath);
		geomId = createShader(geom, GL_GEOMETRY_SHADER);
		glAttachShader(program, geomId);
	}

	glLinkProgram(program);
	glDeleteShader(vtxId);
	glDeleteShader(fgId);
	if (geomPath.length() > 0) glDeleteShader(geomId);
	uprovider.setProgram(program);
}

unsigned int Shader::createShader(std::string& source, GLenum shaderType) {
	unsigned int shader = glCreateShader(shaderType);

	const char* srcPtr = source.c_str();
	glShaderSource(shader, 1, &srcPtr, NULL);

	glCompileShader(shader);

	int compiled = true;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);
		glDeleteShader(shader);
		throw std::logic_error(&errorLog[0]);
	}
	return shader;
}