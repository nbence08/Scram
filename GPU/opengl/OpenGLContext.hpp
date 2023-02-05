#pragma once
#include <stdexcept>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Quaternion.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "Math_Functions.hpp"
#include <limits>
#include <iostream>

/// <summary>
/// class which creates the GLFW openglcontext and opengl window
/// it also handles mouse and keyboard inputs
/// </summary>
class OpenGLContext {
public:
	GLFWwindow* window;
	void init();
	double cursorX, cursorY;
	double xDeg, yDeg;
	double moveSpeed, cursorSpeed;
	bool first;

	OpenGLContext();

	void handleInputs(PerspectiveCamera& camera, real_t deltaTime);
};
