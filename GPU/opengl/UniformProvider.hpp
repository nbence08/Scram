#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "GL/glew.h"

#include "Preprocess_Definitions.hpp"

#include "GPU_export.hpp"

namespace ScMath {
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix4;
}
namespace ScOpenGL {
	class TextureUnit;
}
namespace SComponent {
	class DirectionalLight;
	class PointLight;
	class Material;
}

namespace ScOpenGL {
	class GPU_EXPORT UniformProvider {
		std::unordered_map<std::string, unsigned int> locationCache;

		/*std::unordered_map<std::string,
			std::variant<float, double, int, Vector2, ScMath::Vector3, ScMath::Vector4, Matrix3, ScMath::Matrix4>
		> valueCache;*/

		unsigned int programId;

		unsigned int getUniformLocation(std::string name);
	public:
		inline UniformProvider() { programId = 0; }
		inline UniformProvider(unsigned int programId) :programId(programId) {}
		void setUniform(std::string name, bool value);
		void setUniform(std::string name, float value);
		void setUniform(std::string name, double value);
		void setUniform(std::string name, const real_t x, const real_t y);
		void setUniform(std::string name, const ScMath::Vector3& value);
		void setUniform(std::string name, const ScMath::Vector4& value);
		void setUniform(std::string name, const ScMath::Matrix4& value);
		void setUniform(std::string name, const int value);
		void setTexture(std::string samplerName, const TextureUnit& unit);
	};
	
}
