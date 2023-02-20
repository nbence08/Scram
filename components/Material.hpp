#pragma once
#include <unordered_map>
#include <variant>

#include "ComponentBase.hpp"
#include "Vector3.hpp"
#include "Texture2D.hpp"
#include "Preprocess_Definitions.hpp"

namespace SComponent {
	//TODO: doesn't work when using doubles as real_t
	//Cook-Torrance material
	class Material : public ComponentBase {
	public:

		Material() {
			metalness = 0.5;
			smoothness = 0.5;
		}

		std::variant<ScMath::Vector3, std::shared_ptr<ScOpenGL::Texture2D>> albedo;
		std::variant<ScMath::Vector3, std::shared_ptr<ScOpenGL::Texture2D>> emission;
		real_t smoothness;
		real_t metalness;

		inline bool hasAlbedoTexture() const {
			return albedo.index() == 1;
		}

		inline bool hasAlbedoVector() const {
			return albedo.index() == 0;
		}

		inline bool hasEmission() const {
			return !emission.valueless_by_exception();
		}

		inline bool hasEmissionTexture() const {
			return emission.index() == 1;
		}

		inline bool hasEmissionVector() const {
			return emission.index() == 0;
		}
	};

	static std::unordered_map<int, Material*> materials;
}
