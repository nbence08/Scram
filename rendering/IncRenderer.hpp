#pragma once

#include "rendering_export.hpp"

#include <memory>
#include <vector>
#include <string>

#include "Pass.hpp"

namespace ScRendering{

	class Scene;

	//incremental renderer
	class RENDERING_EXPORT IncRenderer {

		std::vector<std::shared_ptr<Pass>> preProcess;
		std::shared_ptr<Pass> process;
		std::vector<std::shared_ptr<Pass>> postProcess;

		void addDefaultPasses();
		void addPreProcessPass(Pass&& pass);

		void addProcessPass(Pass&& pass);

		void addPostProcessPass(Pass&& pass);

		void setLight(const SComponent::PointLight& light, int index, std::string arrayName);
		void setLight(const SComponent::DirectionalLight& light, int index, std::string arrayName);
		void setMaterial(const SComponent::Material& material, int index, std::string arrayName);

	public:
		IncRenderer(std::string defaultShaderName = "shaders/incremental");
		void setCullFace(bool cullFace);
		void draw(Scene& scene);
	};

}
