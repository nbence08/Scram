#pragma once
#include "core/OpenGL/ShaderProgram.h"
#include "core/OpenGL/Framebuffer.h"

enum class PassType {
	preProcess,
	process,
	postProcess
};

class Pass {
	std::shared_ptr<ShaderProgram> program;
	std::shared_ptr<Framebuffer> fbo;

	std::vector<std::shared_ptr<Texture2D>> inputs;
	std::vector<std::shared_ptr<Texture2D>> outputs;
};

