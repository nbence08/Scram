#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "GL/glew.h"
#include "core/math/linear_algebra.hpp"
#include "TextureUnit.h"
#include "components/PointLight.h"
#include "components/DirectionalLight.h"
#include "components/CTMaterial.h"

class UniformProvider{
	std::unordered_map<std::string, unsigned int> locationCache;
	
	/*std::unordered_map<std::string,
		std::variant<float, double, int, Vector2, Vector3, Vector4, Matrix3, Matrix4>
	> valueCache;*/
	
	//TOTO: add tracking to track uniform array indexes, so no need to specify array indices

	unsigned int programId;

	unsigned int getUniformLocation(std::string name) {
		if (locationCache.find(name) == end(locationCache)) {
			unsigned int location = glGetUniformLocation(programId, name.c_str());
			locationCache.insert({name, location});
			return location;
		}
		else {
			return locationCache[name];
		}
	}
public:
	UniformProvider() { programId = 0; }
	UniformProvider(unsigned int programId):programId(programId) {}


	void setUniform(std::string name, bool value) {
		setUniform(name, (int)value);
	}


	void setUniform(std::string name, float value) {
		unsigned int location = getUniformLocation(name);
		
		glUniform1f(location, value);
	}

	void setUniform(std::string name, double value) {
		unsigned int location = getUniformLocation(name);

		glUniform1d(location, value);
	}

	void setUniform(std::string name, const real_t x, const real_t y) {
		unsigned int location = getUniformLocation(name);
		if (GL_REAL == GL_FLOAT) {
			glUniform2f(location, x, y);
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniform2d(location, x, y);
		}
	}

	void setUniform(std::string name, const Vector3& value) {
		unsigned int location = getUniformLocation(name);
		if (GL_REAL == GL_FLOAT) {
			glUniform3f(location, value.x, value.y, value.z);
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniform3d(location, value.x, value.y, value.z);
		}
	}

	void setUniform(std::string name, const Vector4& value) {
		unsigned int location = getUniformLocation(name);
		if (GL_REAL == GL_FLOAT) {
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniform4d(location, value.x, value.y, value.z, value.w);
		}
	}

	void setUniform(std::string name, const Matrix4& value) {
		unsigned int location = getUniformLocation(name);

		if (GL_REAL == GL_FLOAT) {
			glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value));
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniformMatrix4dv(location, 1, GL_FALSE, reinterpret_cast<const GLdouble*>(&value));
		}
	}

	void setUniform(std::string name, const int value) {
		unsigned int location = getUniformLocation(name);

		glUniform1i(location, value);
	}

	void setTexture(std::string samplerName, const TextureUnit& unit) {
		unsigned int location = getUniformLocation(samplerName);

		glUniform1i(location, unit.getUnitNum());
	}


	void setLight(const PointLight& light, int index, std::string arrayName = "pointLights") {
		setUniform(arrayName + "[" + std::to_string(index) + "].intensity", light.intensity);
		setUniform(arrayName + "[" + std::to_string(index) + "].attenuation", light.attenuation);
		setUniform(arrayName + "[" + std::to_string(index) + "].position", light.position);
	}

	void setLight(const DirectionalLight& light, int index, std::string arrayName = "dirLights") {
		setUniform(arrayName + "[" + std::to_string(index) + "].intensity", light.intensity);
		setUniform(arrayName + "[" + std::to_string(index) + "].direction", light.direction.normalized());
	}

	//TODO: add setLight for SpotLights

	void setMaterial(const CTMaterial& material,int index, std::string arrayName = "materials") {
		bool albedo_is_texture;
		if (material.albedo.index() == 0) { //Vector3
			
			Vector3 albedo = std::get<Vector3>(material.albedo);
			albedo_is_texture = false;

			setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", 0);
			setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", albedo);
		}
		else { //Texture
			
			Texture2D& albedo = *std::get<std::shared_ptr<Texture2D>>(material.albedo);
			auto textureUnit = albedo.getTextureUnitNum();
			if (textureUnit == -1) {
				//TODO: automatic texture unit creation could be implemented in the future
				Vector3 albedo(1.0, 0.0, 1.0);
				albedo_is_texture = false;

				setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", 0);
				setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", albedo);
			}
			albedo_is_texture = true;
			setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", Vector3(0.0, 0.0, 0.0));
			setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", textureUnit);
		}

		setUniform(arrayName + "[" + std::to_string(index) + "].albedo_is_texture", albedo_is_texture);
		setUniform(arrayName + "[" + std::to_string(index) + "].smoothness", material.smoothness);
		setUniform(arrayName + "[" + std::to_string(index) + "].metalness", material.metalness);

		if (material.hasEmission()) {
			if (material.hasEmissionTexture()) {
				const auto tex = std::get<std::shared_ptr<Texture2D>>(material.emission);
				setUniform(arrayName + "[" + std::to_string(index) + "].has_emission", true);
				setUniform(arrayName + "[" + std::to_string(index) + "].emissionTexture", tex->getTextureUnitNum());
			}
			else if (material.hasEmissionVector()) {
				//ISSUE: constant emission vector is not supported, to be mended
				setUniform(arrayName + "[" + std::to_string(index) + "].has_emission", false);
			}
		}
	}

};

