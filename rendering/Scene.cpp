#include "Scene.h"

Scene::Scene() {
	camera = std::make_shared<PerspectiveCamera>();
}