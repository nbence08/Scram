#include "OpenGLContext.h"
#include "core/Global_Props.hpp"

void __stdcall errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::string sSource;
	switch (source) {
		case GL_DEBUG_SOURCE_API:
			sSource = "Source:GL_DEBUG_SOURCE_API\n";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			sSource = "Source:GL_DEBUG_SOURCE_WINDOW_SYSTEM\n";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			sSource = "Source:GL_DEBUG_SOURCE_SHADER_COMPILER\n";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			sSource = "Source:GL_DEBUG_SOURCE_THIRD_PARTY\n";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			sSource = "Source:GL_DEBUG_SOURCE_APPLICATION\n";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			sSource = "Source:GL_DEBUG_SOURCE_OTHER\n";
			break;
	}
	std::string sType;
	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			sType = "Type:GL_DEBUG_TYPE_ERROR\n";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			sType = "Type:GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR\n";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			sType = "Type:GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR\n";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			sType = "Type:GL_DEBUG_TYPE_PORTABILITY\n";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			sType = "Type:GL_DEBUG_TYPE_PERFORMANCE\n";
			break;
		case GL_DEBUG_TYPE_MARKER:
			sType = "Type:GL_DEBUG_TYPE_MARKER\n";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			sType = "Type:GL_DEBUG_TYPE_PUSH_GROUP\n";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			sType = "Type:GL_DEBUG_TYPE_POP_GROUP\n";
			break;
		case GL_DEBUG_TYPE_OTHER:
			sType = "Type:GL_DEBUG_TYPE_OTHER\n";
			break;
	}

	std::string sSeverity;
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			sSeverity = "Severity:GL_DEBUG_SEVERITY_HIGH\n";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			sSeverity = "Severity:GL_DEBUG_SEVERITY_MEDIUM\n";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			sSeverity = "Severity:GL_DEBUG_SEVERITY_LOW\n";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			sSeverity = "Severity:GL_DEBUG_SEVERITY_NOTIFICATION\n";
			break;
	}

	std::cout <<sSource << sType << "Id:" << id <<'\n' << sSeverity << message << '\n' << std::endl;
	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		throw std::exception(message);
	}
}


void OpenGLContext::init() {

	if (glfwInit() != GLFW_TRUE) {
		throw std::runtime_error("Unable to initialize glfw");
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(global::screenWidth, global::screenHeight, "OpenGL window", nullptr, nullptr);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);

	auto glewResult = glewInit();
	if (glewResult) {
		const char* glewResultString = reinterpret_cast<const char*>(glewGetErrorString(glewResult));
		throw std::runtime_error(glewResultString);
	}

	glEnable(GL_DEBUG_OUTPUT);

	glDebugMessageCallback(errorCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}