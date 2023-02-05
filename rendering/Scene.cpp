#include "Scene.hpp"

namespace ScRendering {
	Scene::Scene() {
		camera = std::make_shared<SComponent::PerspectiveCamera>();
	}
}
