#pragma once

#include <bitset>
#include <stdexcept>
#include <string>

#include "core/math/linear_algebra.hpp"
#include "core/OpenGL/Texture2D.hpp"

#include "components/Mesh.hpp"
#include "components/ComponentBase.hpp"
#include "components/Transform.hpp"

namespace SComponent {
	class Mesh;

	class Entity {
		std::vector<std::shared_ptr<Mesh>> meshes;
		std::vector<std::shared_ptr<ScOpenGL::Texture2D>> textures;

		std::vector<std::shared_ptr<ComponentBase>> components;
		std::bitset<MAX_COMPONENTS> componentBits;

		std::vector<std::shared_ptr<Entity>> children;
		Entity* parent;

	public:
		inline std::vector<std::shared_ptr<Mesh>>& getMeshes() { return meshes; }
		inline std::vector<std::shared_ptr<ScOpenGL::Texture2D>>& getTextures() { return textures; }

		Entity();

		template <typename T>
		bool hasComponent() {
			int typeId = getTypeId<T>();

			return componentBits.test(typeId);
		}

		template <typename T>
		void addComponent() {
			int typeId = getTypeId<T>();

			if (componentBits.test(typeId)) {
				components.at(typeId).reset();
			}

			components.at(typeId) = std::make_shared<T>();
			componentBits.set(typeId);
		}

		template <typename T>
		void addComponent(T&& component) {
			int typeId = getTypeId<T>();

			if (componentBits.test(typeId)) {
				components.at(typeId).reset();
			}

			components.at(typeId) = std::make_shared<T>(std::forward<T>(component));
			componentBits.set(typeId);
		}

		template <typename T>
		T& getComponent() {
			int typeId = getTypeId<T>();
			if (componentBits.test(typeId)) {
				T* t = static_cast<T*>(components[typeId].get());
				return *t;
			}
			else {
				throw std::domain_error("Enttiy does not contain component of type: " + std::to_string(typeId));
			}
		}

		template <typename T>
		void removeComponent() {
			int typeId = getTypeId<T>();
			if (componentBits.test(typeId)) {
				components.at(typeId).reset();

			}
		}

		std::shared_ptr<Entity> createChild();

		std::vector<std::shared_ptr<Entity>>& getChildren();

		Smath::Matrix4 model();
	};
}

