#include "Scene.hpp"

namespace ScRendering {

	Scene::Scene() {
		camera = std::make_shared<SComponent::PerspectiveCamera>();
	}

	void Scene::addObject(std::shared_ptr<SComponent::Entity> model) {
		objects.emplace_back(model);
	}

	std::vector<std::shared_ptr<SComponent::Entity>>& Scene::getObjects() { return objects; }
	std::vector<SComponent::DirectionalLight>& Scene::getDirLights() { return dirLights; }
	std::vector<SComponent::PointLight>& Scene::getPointLights() { return pointLights; }
	std::vector<SComponent::SpotLight>& Scene::getSpotLights() { return spotLights; }
	SComponent::PerspectiveCamera& Scene::getCamera() { return *camera; }
	void Scene::setCamera(SComponent::PerspectiveCamera& camera) { this->camera = std::make_shared<SComponent::PerspectiveCamera>(camera); }
	void Scene::setCamera(std::shared_ptr<SComponent::PerspectiveCamera> camera) { this->camera = camera; }

}
