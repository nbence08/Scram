#pragma once

#include <iostream>
#include <fstream>
#include <iterator>

#include "OpenGLContext.hpp"
#include "IncRenderer.hpp"
#include "Entity.hpp"
#include "IO.hpp"
#include "DirectionalLight.hpp"
#include "Scene.hpp"
#include "TextureUnit.hpp"

extern int SComponent::componentTypeCounter = 0;

int main() {

	ScOpenGL::OpenGLContext context;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	try {
		context.init();
	}
	catch (std::runtime_error err) {
		std::cout << err.what() <<"\n";
		return EXIT_FAILURE;
	}

	auto currentFrame = glfwGetTime();
	auto lastFrame = glfwGetTime();
	
	std::shared_ptr<SComponent::Entity> ent = 
	ScIO::importModelFromFile("../resources/models/bsg_pegasus.glb");
	std::shared_ptr<SComponent::Entity> ent2 = ScIO::importModelFromFile("../resources/models/box.glb");

	auto& entTransform = ent->getComponent<SComponent::Transform>();
	auto& ent2Transform = ent2->getComponent<SComponent::Transform>();
	
	entTransform.setRotation(ScMath::Vector3(PI / 2.0, 0.0, 0.0));
	entTransform.setScale(ScMath::Vector3(0.5, 0.5, 0.5));
	ent2Transform.setTranslation(ScMath::Vector3(0.0, 40.0f, 0.0));

	ScRendering::Scene scene;
	scene.getCamera().setFarPlane(2000.0f);

	SComponent::DirectionalLight sun;
	sun.direction = ScMath::Vector3(1.0f, 1.0f, 1.0f);
	sun.intensity = ScMath::Vector3(10.0f, 10.0f, 9.0f);
	scene.getDirLights().push_back(sun);

	SComponent::PointLight intense;
	intense.attenuation = ScMath::Vector3(0.0, 0.0, 0.2);
	intense.intensity = ScMath::Vector3(1.0, 100.0, 1.0);
	intense.position = ScMath::Vector3(0.0, -30.0, -78.0);
	scene.getPointLights().push_back(intense);

	ScRendering::IncRenderer renderer;

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

	ScOpenGL::clearTextureUnits();
	glfwTerminate();
	return EXIT_SUCCESS;
}
