#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <functional>
#include <vector>

#include "ConstantHolder.h"
#include "Camera.h"
#include "Renderer.h"
#include "BasicRenderer.h"

class Window;

static std::shared_ptr<Camera> camera = std::make_shared<Camera>();

static double lastX;
static double lastY;

static unsigned int staticWidth = 800;
static unsigned int staticHeight = 800;

static float lastFrame = glfwGetTime();
static float diff;


static std::vector<Window*> windows;

//TODO implement Singleton pattern
class Window{
private:
    std::string windowName;
    GLFWwindow* window;
    std::shared_ptr<Renderer> renderer;

public: Window (
                  std::string windowName = "Default")
                  : windowName(windowName) {
        lastFrame = glfwGetTime();
        lastX = 0.0f;
        lastY = 0.0f;
        initLibs();
        setCallbacks();
        glViewport(0, 0, staticWidth, staticHeight);

        windows.push_back(this);

        renderer = std::make_shared<BasicRenderer>(camera, ScreenSize{staticWidth, staticHeight});
    }

public:~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:void initLibs() {
    //  GLEW/GLFW boiler plate init code
        if (!glfwInit())
            throw std::logic_error("Error initializing glfw.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(staticWidth, staticHeight, windowName.c_str(), NULL, NULL);
        if (!window){
            glfwTerminate();
            throw std::logic_error("Error creating glfw window.");
        }

        glfwMakeContextCurrent(window);

        GLenum err = glewInit();
        if (GLEW_OK != err){
            std::stringstream error;
            error << "Error while initializing GLEW: " << glewGetErrorString(err);
            throw new std::logic_error(error.str());
        }
        std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

private: static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    float yDiff = lastY - ypos;
    float xDiff = lastX - xpos;

    lastY = ypos;
    lastX = xpos;

    yDiff *= ConstantHolder::mouseSensitivity;
    xDiff *= ConstantHolder::mouseSensitivity;

    camera->addPitch(yDiff);
    camera->addYaw(xDiff);
}

private: static void window_size_callback(GLFWwindow* window, int width, int height){
    staticWidth = width;
    staticHeight = height;
    glViewport(0, 0, width, height);
    camera->setAspectRatio((float)width/(float)height);

    //TODO: properly manage the reconstruction of ONLY the framebuffer, and not the reconstruction of the entinre
    //      renderer object
    for (auto window : windows) {
        window->renderer->setScreenSize(width, height);
        window->renderer = std::make_shared<BasicRenderer>(camera, ScreenSize{ staticWidth, staticHeight });
    }
}


private: static void pollInputs(GLFWwindow* window) {
    
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->forward(diff * ConstantHolder::moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->forward(diff * -ConstantHolder::moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->right(diff * ConstantHolder::moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->right(diff * -ConstantHolder::moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }


private: void setCallbacks() {
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);
    }

public: void run() {
    while (!glfwWindowShouldClose(window)) {
        diff = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        renderer->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
        pollInputs(window);
    }
}

};

