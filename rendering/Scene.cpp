#include "Scene.hpp"

Scene::Scene() {
	camera = std::make_shared<SComponent::PerspectiveCamera>();
}