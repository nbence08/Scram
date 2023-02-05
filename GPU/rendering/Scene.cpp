#include "Scene.hpp"

Scene::Scene() {
	camera = std::make_shared<PerspectiveCamera>();
}

void Scene::addObject(std::shared_ptr<Entity> model) {
	objects.emplace_back(model);
}

std::vector<std::shared_ptr<Entity>>& Scene::getObjects() { return objects; }
std::vector<DirectionalLight>& Scene::getDirLights() { return dirLights; }
std::vector<PointLight>& Scene::getPointLights() { return pointLights; }
std::vector<SpotLight>& Scene::getSpotLights() { return spotLights; }
PerspectiveCamera& Scene::getCamera() { return *camera; }
void Scene::setCamera(PerspectiveCamera& camera) { this->camera = std::make_shared<PerspectiveCamera>(camera); }
void Scene::setCamera(std::shared_ptr<PerspectiveCamera> camera) { this->camera = camera; }
