#pragma once

#include <bitset>
#include <stdexcept>
#include <string>

#include "core/math/linear_algebra.hpp"
#include "core/OpenGL/Texture2D.h"

#include "components/Mesh.h"
#include "components/ComponentBase.hpp"
#include "components/Transform.h"
class Mesh;

class Entity{
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<std::shared_ptr<Texture2D>> textures;
	std::bitset<MAX_COMPONENTS> componentBits;

public:
	inline std::vector<std::shared_ptr<Mesh>>& getMeshes(){ return meshes; }
	inline std::vector<std::shared_ptr<Texture2D>>& getTextures() { return textures; }

	Entity() {
		components.resize(MAX_COMPONENTS);
		addComponent(Transform());
	}

	std::vector<std::shared_ptr<ComponentBase>> components;
	Matrix4 model;

	template <typename T>
	void addComponent(T&& component){
		int typeId = component.getTypeId();

		if (componentBits.test(typeId)) {
			components.at(typeId).reset();
		}

		components.at(typeId) = std::make_shared<T>(component);
		componentBits.set(typeId);
	}

	template <typename T>
	T& getComponent() {
		int typeId = getComponentTypeId<T>();
		if (componentBits.test(typeId)) {
			T* t = reinterpret_cast<T*>(components[typeId].get());
			return *t;
		}
		else {
			throw std::domain_error("Enttiy does not contain component of type: "+std::to_string(typeId));
		}
	}

	template <typename T>
	void removeComponent(){
		int typeId = getComponentTypeId<T>();
		if (componentBits.test(typeId)) {
			components.at(typeId).reset();

		}
	}
};

