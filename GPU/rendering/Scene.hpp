#pragma once
#include "Entity.hpp"
#include "SpotLight.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "PerspectiveCamera.hpp"

class Scene{
	std::vector<std::shared_ptr<Entity>> objects;
	std::vector<DirectionalLight> dirLights;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	std::shared_ptr<PerspectiveCamera> camera;

public:
	Scene();

	void addObject(std::shared_ptr<Entity> model);

	std::vector<std::shared_ptr<Entity>>& getObjects();

	//these getter functions could be modified so that there is only a single vector containing std::variants,
	//and the std::variant defines which type of light it contains
	//querying for specific type of lights would be like: getLights<[TYPE_OF_LIGHT]>()
	std::vector<DirectionalLight>& getDirLights();
	std::vector<PointLight>& getPointLights();
	std::vector<SpotLight>& getSpotLights();
	PerspectiveCamera& getCamera();
	void setCamera(PerspectiveCamera& camera);
	void setCamera(std::shared_ptr<PerspectiveCamera> camera);
};

