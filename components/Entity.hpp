#pragma once

#include <bitset>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include <typeinfo>
#include <typeindex>

#include "linear_algebra.hpp"
#include "Texture2D.hpp"

#include "Mesh.hpp"
#include "ComponentBase.hpp"
#include "Transform.hpp"

#include "components_export.hpp"

namespace SComponent {
	class Mesh;

	class COMPONENTS_EXPORT Entity {
		std::vector<std::shared_ptr<Mesh>> meshes;
		std::vector<std::shared_ptr<ScOpenGL::Texture2D>> textures;

		//TODO: make this a multimap
		std::unordered_map<std::type_index, std::shared_ptr<ComponentBase>> components;

		std::vector<std::shared_ptr<Entity>> children;
		Entity* parent;
		std::string modelId;

	public:
		inline std::vector<std::shared_ptr<Mesh>>& getMeshes() { return meshes; }
		inline std::vector<std::shared_ptr<ScOpenGL::Texture2D>>& getTextures() { return textures; }

		void setId (std::string modelId){ this->modelId = modelId; }

		Entity();

		template <Component T>
		bool hasComponent() {
			auto it = components.find(std::type_index(typeid(T)));
			return it != components.end();
		}

		template <Component T>
		void addComponent() {
			auto index = std::type_index(typeid(T));
			components[index] = std::make_shared<T>();
		}

		template <Component T>
		void addComponent(T&& component) {
			auto index = std::type_index(typeid(T));
			components[index] = std::make_shared<T>(std::forward<T>(component));
		}

		template <Component T>
		T& getComponent() {
				try {
					return *static_cast<T*>(components.at(std::type_index(typeid(T))).get());
				}
				catch (...) {
					//std::domain_error("Enttiy does not contain component of type: " + std::to_string(typeId));
					throw;
				}
		}

		template <Component T>
		void removeComponent() {
			components.erase(std::type_index(typeid(T)));
		}

		std::shared_ptr<Entity> createChild();

		std::vector<std::shared_ptr<Entity>>& getChildren();

		ScMath::Matrix4 model();
	};
}

