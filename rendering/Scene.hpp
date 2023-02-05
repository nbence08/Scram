#pragma once
#include "components/Entity.hpp"
#include "components/SpotLight.hpp"
#include "components/PointLight.hpp"
#include "components/DirectionalLight.hpp"
#include "components/PerspectiveCamera.hpp"

class Scene{
	std::vector<std::shared_ptr<SComponent::Entity>> objects;
	std::vector<SComponent::DirectionalLight> dirLights;
	std::vector<SComponent::PointLight> pointLights;
	std::vector<SComponent::SpotLight> spotLights;
	std::shared_ptr<SComponent::PerspectiveCamera> camera;

public:
	Scene();

	inline void addObject(std::shared_ptr<SComponent::Entity> model) {
		objects.emplace_back(model);
	}

	inline std::vector<std::shared_ptr<SComponent::Entity>>& getObjects(){ return objects; }

	//these getter functions could be modified so that there is only a single vector containing std::variants,
	//and the std::variant defines which type of light it contains
	//querying for specific type of lights would be like: getLights<[TYPE_OF_LIGHT]>()
	inline std::vector<SComponent::DirectionalLight>& getDirLights(){ return dirLights; }
	inline std::vector<SComponent::PointLight>& getPointLights() { return pointLights; }
	inline std::vector<SComponent::SpotLight>& getSpotLights() { return spotLights; }
	inline SComponent::PerspectiveCamera& getCamera(){ return *camera; }
	inline void setCamera(SComponent::PerspectiveCamera& camera) { this->camera = std::make_shared<SComponent::PerspectiveCamera>(camera); }
	inline void setCamera(std::shared_ptr<SComponent::PerspectiveCamera> camera) { this->camera = camera; }
};

