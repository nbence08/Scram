#pragma once

extern int componentTypeCounter = 0;

#include <iostream>

#include <fstream>
#include <iterator>

#include "core/OpenGL/OpenGLContext.h"
#include "core/Preprocess_Definitions.h"

#include "core/OpenGL/ShaderProgram.h"
#include "core/math/linear_algebra.hpp"
#include "core/OpenGL/VertexArray.h"
#include "core/OpenGL/Buffer.h"

#include "io/IO.h"
#include "glm/glm.hpp"
#include "components/PerspectiveCamera.h"
#include "components/Transform.h"
#include "components/PointLight.h"
#include "components/DirectionalLight.h"

#include "components/Material.h"
#include "core/CubeData.hpp"

#include "rendering/Scene.h"
#include "rendering/IncRenderer.h"

#include "components/Entity.h"

int main() {

	OpenGLContext context;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	try {
		context.init();
	}
	catch (std::runtime_error err) {
		std::cout << err.what() <<"\n";
		return -1;
	}

	auto currentFrame = glfwGetTime();
	auto lastFrame = glfwGetTime();
	
	std::shared_ptr<Entity> ent = IO::importModelFromFile("resources/models/bsg_pegasus.glb");
	std::shared_ptr<Entity> ent2 = IO::importModelFromFile("resources/models/box.glb");

	auto& entTransform = ent->getComponent<Transform>();
	auto& ent2Transform = ent2->getComponent<Transform>();
	
	entTransform.setRotation(Vector3(PI / 2.0, 0.0, 0.0));
	entTransform.setScale(Vector3(0.5, 0.5, 0.5));
	ent2Transform.setTranslation(Vector3(0.0, 40.0f, 0.0));



	Scene scene;
	scene.getCamera().setFarPlane(2000.0f);

	DirectionalLight sun;
	sun.direction = Vector3(1.0f, 1.0f, 1.0f);
	sun.intensity = Vector3(10.0f, 10.0f, 9.0f);
	scene.getDirLights().push_back(sun);

	PointLight intense;
	intense.attenuation = Vector3(0.0, 0.0, 0.2);
	intense.intensity = Vector3(1.0, 100.0, 1.0);
	intense.position = Vector3(0.0, -30.0, -78.0);
	scene.getPointLights().push_back(intense);

	IncRenderer renderer;

	scene.addObject((ent));
	scene.addObject((ent2));

	context.moveSpeed = 50.0f;

	while (!glfwWindowShouldClose(context.window)) {
		currentFrame = glfwGetTime();
		auto deltaTime = currentFrame - lastFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		context.handleInputs(scene.getCamera(), (real_t)deltaTime);

		renderer.draw(scene);

		glfwSwapBuffers(context.window);

		if (glfwGetKey(context.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(context.window, true);
		}

		glfwPollEvents();
		lastFrame = currentFrame;
	}

	textureUnits.clear();
	glfwTerminate();
}