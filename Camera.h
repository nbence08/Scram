#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <iostream>
#include "ConstantHolder.h"

class Camera{
private:
	glm::vec3 cameraPos;
	float pitch, yaw;
	float aspectRatio;
public:
	Camera() {
		cameraPos = glm::vec3(0.0f, 0.0f, 2.5f);
		pitch = 0.0f;
		yaw = 0.0f;
		aspectRatio = 1.0f;
	}

	inline void setAspectRatio(float aspectRatio) {
		this->aspectRatio = aspectRatio;
	}

	glm::mat4 view() {
		glm::mat4 view(1.0f);

		view = glm::translate(view, cameraPos);
		view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

		return glm::inverse(view);
	}

	glm::mat4 proj() {
		//TODO: these values should be given as parameters, or sg similar later on
			float nearPlane = 0.1f;
			float farPlane = 60.0f;
			float halfFov = fov()*ConstantHolder::PI/180.0f/2.0f;
		//

		float tanVal = tan(halfFov);

		glm::mat4 proj(
			1.0f/(aspectRatio*tanVal), 0.0f,		   0.0f,										 0.0f,
			0.0f,				  1.0f/tanVal, 0.0f,										 0.0f,
			0.0f,				  0.0f,		  -(farPlane+nearPlane)/(farPlane-nearPlane),	-1.0f,
			0.0f,				  0.0f,		  -2.0f*nearPlane*farPlane/(farPlane-nearPlane), 0.0f
		);
		
		return proj;
		//return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	float fov() {
		return 90.0f;
	}

	void addPitch(float diff) {
		pitch += diff;
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
	}

	void addYaw(float diff) {
		yaw += diff;
	}

	void forward(float diff) {
		glm::vec4 ahead(0.0f, 0.0f, -1.0f, 0.0f);
		glm::mat4 view(1.0f);

		view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

		ahead = view*ahead;

		glm::vec3 aheadVec3(ahead.x, ahead.y, ahead.z);

		cameraPos += diff * aheadVec3;
	}

	void right(float diff) {
		glm::vec4 right(1.0f, 0.0f, 0.0f, 0.0f);
		glm::mat4 view(1.0f);

		view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

		right = view * right;

		glm::vec3 aheadVec3(right.x, right.y, right.z);

		cameraPos += diff * aheadVec3;
	}
};

