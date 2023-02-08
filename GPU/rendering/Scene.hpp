#pragma once
#include "Entity.hpp"
#include "SpotLight.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "PerspectiveCamera.hpp"

namespace ScRendering{

	class Scene{
		std::vector<std::shared_ptr<SComponent::Entity>> objects;
		std::vector<SComponent::DirectionalLight> dirLights;
		std::vector<SComponent::PointLight> pointLights;
		std::vector<SComponent::SpotLight> spotLights;
		std::shared_ptr<SComponent::PerspectiveCamera> camera;

	public:
		Scene();

		void addObject(std::shared_ptr<SComponent::Entity> model);

		std::vector<std::shared_ptr<SComponent::Entity>>& getObjects();

		//these getter functions could be modified so that there is only a single vector containing std::variants,
		//and the std::variant defines which type of light it contains
		//querying for specific type of lights would be like: getLights<[TYPE_OF_LIGHT]>()
		std::vector<SComponent::DirectionalLight>& getDirLights();
		std::vector<SComponent::PointLight>& getPointLights();
		std::vector<SComponent::SpotLight>& getSpotLights();
		SComponent::PerspectiveCamera& getCamera();
		void setCamera(SComponent::PerspectiveCamera& camera);
		void setCamera(std::shared_ptr<SComponent::PerspectiveCamera> camera);
	};

}
