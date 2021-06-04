#pragma once
#include <GL/glew.h>
#include <iostream>
#include <functional>

namespace OpenGlOperations {
    static std::function<std::string(unsigned int)> convertError = [](unsigned int errorCode) -> std::string {
        switch (errorCode) {
        case GL_NO_ERROR:
            return std::string("NO ERROR");
            break;

        case GL_INVALID_ENUM:
            return std::string("INVALID ENUM");
            break;

        case GL_INVALID_VALUE:
            return std::string("INVALID VALUE");
            break;

        case GL_INVALID_OPERATION:
            return std::string("INVALID OPERATION");
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return std::string("INVALID FRAMEBUFFER OPERATION");
            break;

        case GL_OUT_OF_MEMORY:
            return std::string("OUT OF MEMORY");
            break;

        default:
            return std::string("UNKNOWN");
        }
    };


    static std::function<void()> checkError = [](){
        auto error = glGetError();
        if (error != GL_NO_ERROR)
            std::cout << "ERROR: " << convertError(error) << std::endl;
        else std::cout << "NO ERROR" << std::endl;
    };

}