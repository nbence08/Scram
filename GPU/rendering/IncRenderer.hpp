#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace ScRendering{

	class Pass;
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
