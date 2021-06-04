#pragma once
#include "Camera.h"

class Renderer {
public: virtual void setCamera(std::shared_ptr<Camera> camera) = 0;
public: virtual void render() = 0;
virtual void setScreenSize(unsigned int width, unsigned int height) = 0;
};