#pragma once
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

#include "components/PointLight.h"
#include "components/DirectionalLight.h"

#include "components/CTMaterial.h"
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
	
	//model->model = math::scale(0.05f, 0.05f, 0.05f)*math::rotate(PI/2.0, Vector3(1.0, 0.0, 0.0));
	
	std::shared_ptr<Entity> ent = IO::importModelFromFile("resources/models/bsg_pegasus.glb");
	std::shared_ptr<Entity> ent2 = IO::importModelFromFile("resources/models/box.glb");
	
	ent->model = math::translate(0.0, 0.0, 0.0) * math::rotate(PI / 2.0, Vector3(1.0, 0.0, 0.0)) * math::scale(0.5f, 0.5f, 0.5f);
	ent2->model = math::translate(Vector3(0.0f, 40.0f, 0.0f));

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

		/*auto cam = scene.getCamera().getPosition();
		std::cout << "X: " << cam.x << " Y: " << cam.y << " Z: " << cam.z << '\n';*/

		renderer.draw(scene);

		glfwSwapBuffers(context.window);

		if (glfwGetKey(context.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(context.window, true);
		}

		glfwPollEvents();
		lastFrame = currentFrame;
	}


	/*catch (std::exception e) {
		std::cout << e.what() << "\n";
		return -1;
	}*/
	textureUnits.clear();
	glfwTerminate();
}

// #include <iomanip>
//Matrix4 mat(1.0f, 2.3f, 2.4f, 1.0f,
//			0.0f, 0.0f, 0.0f, 0.0f,
//			1.0f, 2.0f, 3.0f, 4.0f,
//			0.0f, 0.0f, 0.0f, 1.0f);

//std::cout << sizeof(mat) << "\n";
//uint8_t* ptr = reinterpret_cast<uint8_t*>(&mat);

//for (int i = 0; i < sizeof(mat); i++) {
//	
//	std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)*ptr++;
//	std::cout << " ";
//	if(i % 4 == 3) std::cout << "| ";
//}
//return 0;