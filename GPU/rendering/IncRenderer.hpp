#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Pass.hpp"

namespace ScRendering{

	class Scene;

	//incremental renderer
	class IncRenderer {

		std::vector<std::shared_ptr<Pass>> preProcess;
		std::shared_ptr<Pass> process;
		std::vector<std::shared_ptr<Pass>> postProcess;

		void addDefaultPasses();
		void addPreProcessPass(Pass&& pass);

		void addProcessPass(Pass&& pass);

		void addPostProcessPass(Pass&& pass);

	public:
		IncRenderer(std::string defaultShaderName = "shaders/incremental");
		void setCullFace(bool cullFace);
		void draw(Scene& scene);
	};

}
