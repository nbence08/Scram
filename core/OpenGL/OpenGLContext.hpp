#pragma once
#include <stdexcept>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "core/math/Quaternion.hpp"
#include "components/PerspectiveCamera.hpp"
#include "core/math/Vector3.hpp"
#include "core/math/Math_Functions.hpp"
#include <limits>
#include <iostream>

namespace ScOpenGL {
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

		OpenGLContext() :window(nullptr) {

			cursorX = 0.0;
			cursorY = 0.0;
			xDeg = 0.0;
			yDeg = 0;
			first = false;
			moveSpeed = 1.0;
			cursorSpeed = 1.0;
		}
#pragma warning (push)
#pragma warning (disable : 4244)
		void handleInputs(SComponent::PerspectiveCamera& camera, real_t deltaTime) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				camera.moveForward(deltaTime * moveSpeed);
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				camera.moveBackward(deltaTime * moveSpeed);
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				camera.moveRightward(deltaTime * moveSpeed);
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				camera.moveLeftward(deltaTime * moveSpeed);
			}

			if (first) {
				first = false;
				glfwGetCursorPos(window, &cursorX, &cursorY);
				return;
			}

			double curCursorX, curCursorY;
			glfwGetCursorPos(window, &curCursorX, &curCursorY);

			double diffX = (-curCursorX + cursorX) * cursorSpeed;
			double diffY = (-curCursorY + cursorY) * cursorSpeed;

			camera.updateForward(diffX, diffY);

			cursorX = curCursorX;
			cursorY = curCursorY;
		}
#pragma warning (pop)
	};
}

