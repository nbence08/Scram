#pragma once
#include "components/Entity.hpp"
#include "components/SpotLight.hpp"
#include "components/PointLight.hpp"
#include "components/DirectionalLight.hpp"
#include "components/PerspectiveCamera.hpp"

class Scene{
	std::vector<std::shared_ptr<Entity>> objects;
	std::vector<DirectionalLight> dirLights;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	std::shared_ptr<PerspectiveCamera> camera;

public:
	Scene();

	inline void addObject(std::shared_ptr<Entity> model) {
		objects.emplace_back(model);
	}

	inline std::vector<std::shared_ptr<Entity>>& getObjects(){ return objects; }

	//these getter functions could be modified so that there is only a single vector containing std::variants,
	//and the std::variant defines which type of light it contains
	//querying for specific type of lights would be like: getLights<[TYPE_OF_LIGHT]>()
	inline std::vector<DirectionalLight>& getDirLights(){ return dirLights; }
	inline std::vector<PointLight>& getPointLights() { return pointLights; }
	inline std::vector<SpotLight>& getSpotLights() { return spotLights; }
	inline PerspectiveCamera& getCamera(){ return *camera; }
	inline void setCamera(PerspectiveCamera& camera) { this->camera = std::make_shared<PerspectiveCamera>(camera); }
	inline void setCamera(std::shared_ptr<PerspectiveCamera> camera) { this->camera = camera; }
};

