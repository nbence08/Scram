#pragma once
#include <stdexcept>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "Math_Functions.hpp"
#include <limits>
#include <iostream>
#include <functional>

#include "GPU_export.hpp"

namespace ScOpenGL {

	void GPU_EXPORT __stdcall errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	//to be abolished, when new windowing module will be introduced
	class GPU_EXPORT InputSinkFacade {
	public:
		std::function<void(real_t)> moveForward;
		std::function<void(real_t)> moveBackward;
		std::function<void(real_t)> moveRightward;
		std::function<void(real_t)> moveLeftward;
		std::function<void(real_t, real_t)> updateForward;
	};

	/// <summary>
	/// class which creates the GLFW openglcontext and opengl window
	/// it also handles mouse and keyboard inputs
	/// </summary>
	class GPU_EXPORT OpenGLContext {
	public:
		GLFWwindow* window;
		void init();
		double cursorX, cursorY;
		double xDeg, yDeg;
		double moveSpeed, cursorSpeed;
		bool first;

		OpenGLContext();

		void setWindow(GLFWwindow* window) {this->window = window;}
		void handleInputs(InputSinkFacade& camera, real_t deltaTime);

		bool windowShouldClose();
		void swapBuffers();
		int getKey (int key);
		void setWindowShouldClose (bool value);
		void pollEvents();
		double getTime();
		void terminate();
	};
}
