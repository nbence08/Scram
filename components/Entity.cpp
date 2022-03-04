#include "Entity.h"

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

SMath::Matrix4 Entity::model() {
	auto transformId = getTypeId<Transform>();
	if (componentBits.test(transformId)) {
		if (parent != nullptr) {
			return parent->model() * getComponent<Transform>().model();
		}
		else {
			return getComponent<Transform>().model();
		}
	}
	else {
		return SMath::Matrix4();
	}
}