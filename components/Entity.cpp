#include "Entity.hpp"

namespace SComponent {
	Entity::Entity() {
		components.resize(MAX_COMPONENTS);
		addComponent<Transform>(Transform());
		parent = nullptr;
	}

	std::shared_ptr<Entity> Entity::createChild() {
		children.push_back(std::make_shared<Entity>());
		auto child = children[children.size() - 1];
		child->parent = this;
		return child;
	}

	std::vector<std::shared_ptr<Entity>>& Entity::getChildren() {
		return children;
	}

	ScMath::Matrix4 Entity::model() {
		if (hasComponent<Transform>()) {
			if (parent != nullptr) {
				return parent->model() * getComponent<Transform>().model();
			}
			else {
				return getComponent<Transform>().model();
			}
		}
		else {
			return ScMath::Matrix4();
		}
	}
}
