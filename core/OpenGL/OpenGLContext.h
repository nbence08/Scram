#pragma once
#include <stdexcept>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "core/math/Quaternion.h"
#include "components/PerspectiveCamera.h"
#include "core/math/Vector3.h"
#include "core/math/Math_Functions.hpp"
#include <limits>
#include <iostream>

class OpenGLContext {
public:
	GLFWwindow* window;
	void init();
	double cursorX, cursorY;
	double xDeg, yDeg;
	double moveSpeed, cursorSpeed;
	bool first;

	OpenGLContext():window(nullptr) {
		
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
	void handleInputs(PerspectiveCamera& camera, real_t deltaTime) {
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

		SMath::Vector3 forward(0.0, 0.0, -1.0);
		SMath::Vector3 up(0.0, 1.0, 0.0);
		SMath::Vector3 right = cross(forward, up);

		double diffX = (- curCursorX + cursorX)*cursorSpeed;
		double diffY = (- curCursorY + cursorY)*cursorSpeed;

		xDeg += diffX;
		yDeg += diffY;

		if(yDeg < -89.0) yDeg = -89.0;
		if(yDeg > 89.0) yDeg = 89.0;
		
		//std::cout << "X:" << xDeg << " Y:" << yDeg << "\n";

		auto yRot = SMath::Quaternion::rotation(math::toRadians(yDeg), right).getRotationMatrix();
		auto xRot = SMath::Quaternion::rotation(math::toRadians(xDeg), up).getRotationMatrix();

		SMath::Vector3 newForward = xRot * (yRot * forward);
		SMath::Vector3 newUp = xRot * (yRot * up);
		camera.setForward( SMath::Vector4(newForward.x, newForward.y, newForward.z, 0.0));
		camera.setUp( SMath::Vector4(newUp.x, newUp.y, newUp.z, 0.0));
		cursorX = curCursorX;
		cursorY = curCursorY;
	}
	#pragma warning (pop)

};


