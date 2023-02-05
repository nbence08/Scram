#include "UniformProvider.hpp"

/// <summary>
/// Gets the location identifier of a uniform variable in the shader 
/// with name supplied as parameter. It caches the locations of the uniforms.
/// It uses the class member locationCache, which is an std::unordered_map<std::string, unsigned int>
/// </summary>
/// <param name="name">Name of the uniform in the shader, whose location is to be queried</param>
/// <returns>Location identifier of the uniform</returns>
unsigned int UniformProvider::getUniformLocation(std::string name) {
	if (locationCache.find(name) == end(locationCache)) {
		unsigned int location = glGetUniformLocation(programId, name.c_str());
		locationCache.insert({ name, location });
		return location;
	}
	else {
		return locationCache[name];
	}
}

/// <summary>
/// Sets bool uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">bool value set as uniform</param>
void UniformProvider::setUniform(std::string name, bool value) {
	setUniform(name, (int)value);
}

/// <summary>
/// Sets float uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">float value set as uniform</param>
void UniformProvider::setUniform(std::string name, float value) {
	unsigned int location = getUniformLocation(name);

	glUniform1f(location, value);
}

/// <summary>
/// Sets double uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">double value set as uniform</param>
void UniformProvider::setUniform(std::string name, double value) {
	unsigned int location = getUniformLocation(name);

	glUniform1d(location, value);
}

/// <summary>
/// Sets vec2 uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="x">real value set as first coordinate of vec2 uniform</param>
/// <param name="y">real value set as second coordinate of vec2 uniform</param>
void UniformProvider::setUniform(std::string name, const real_t x, const real_t y) {
	unsigned int location = getUniformLocation(name);
	if (GL_REAL == GL_FLOAT) {
		glUniform2f(location, x, y);
	}
	else if (GL_REAL == GL_DOUBLE) {
		glUniform2d(location, x, y);
	}
}

/// <summary>
/// Sets vec3 uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to. Uses float or double version of glUniform,
/// based on the preprocessor configuration
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">Smath::Vector3 value set as uniform</param>
void UniformProvider::setUniform(std::string name, const Smath::Vector3& value) {
	unsigned int location = getUniformLocation(name);
	if (GL_REAL == GL_FLOAT) {
		glUniform3f(location, value.x, value.y, value.z);
	}
	else if (GL_REAL == GL_DOUBLE) {
		glUniform3d(location, value.x, value.y, value.z);
	}
}

/// <summary>
/// Sets vec4 uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to. Uses float or double version of glUniform,
/// based on the preprocessor configuration
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">Vector4 value set as uniform</param>
void UniformProvider::setUniform(std::string name, const Smath::Vector4& value) {
	unsigned int location = getUniformLocation(name);
	if (GL_REAL == GL_FLOAT) {
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	else if (GL_REAL == GL_DOUBLE) {
		glUniform4d(location, value.x, value.y, value.z, value.w);
	}
}

/// <summary>
/// Sets mat4 uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to. Uses float or double version of glUniform,
/// based on the preprocessor configuration
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">Smath::Matrix4 value set as uniform</param>
void UniformProvider::setUniform(std::string name, const Smath::Matrix4& value) {
	unsigned int location = getUniformLocation(name);

	if (GL_REAL == GL_FLOAT) {
		glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value));
	}
	else if (GL_REAL == GL_DOUBLE) {
		glUniformMatrix4dv(location, 1, GL_FALSE, reinterpret_cast<const GLdouble*>(&value));
	}
}

/// <summary>
/// Sets int uniform value, identified by the name specified as parameter, in the 
/// shader program it is attached to.
/// </summary>
/// <param name="name">Name of the uniform variable in the shader</param>
/// <param name="value">int value set as uniform</param>
void UniformProvider::setUniform(std::string name, const int value) {
	unsigned int location = getUniformLocation(name);

	glUniform1i(location, value);
}

/// <summary>
/// Sets texture unit value, identified by the name specified as parameter, in the 
/// shader program it is attached to.
/// </summary>
/// <param name="name">Name of the sampler in the shader</param>
/// <param name="unit">Id of the texture unit to be set</param>
void UniformProvider::setTexture(std::string samplerName, const TextureUnit& unit) {
	unsigned int location = getUniformLocation(samplerName);

	glUniform1i(location, unit.getUnitNum());
}

/// <summary>
/// Sets point light source in the shader. Performs shadow map setting as well if
/// a shadow texture is available on light.
/// </summary>
/// <param name="light">Point light source to bet set</param>
/// <param name="index">Index of the point light source to be set in the shader, in the array of point lights</param>
/// <param name="arrayName">Name of the array containing the point light data in the shader. Default=["pointLights"]</param>
void UniformProvider::setLight(const SComponent::PointLight& light, int index, std::string arrayName) {
	setUniform(arrayName + "[" + std::to_string(index) + "].intensity", light.intensity);
	setUniform(arrayName + "[" + std::to_string(index) + "].attenuation", light.attenuation);
	setUniform(arrayName + "[" + std::to_string(index) + "].position", light.position);
	if (light.hasShadowMap()) {
		setUniform(arrayName + "ShadowMap[" + std::to_string(index) + "]", light.shadowMap->getTextureUnitNum());
		auto lightSpaceMatrices = light.getLightSpaceMatrices();
		setUniform(arrayName + "[" + std::to_string(index) + "].farPlane", light.farPlane);
		for (int i = 0; i < 6; i++) {
			setUniform(arrayName + "[" + std::to_string(index) + "].lightMatrices[" + std::to_string(i) + "]", lightSpaceMatrices[i]);
		}
	}
}

/// <summary>
/// Sets directional light source in the shader. Performs shadow map setting as well if
/// a shadow texture is available on light.
/// </summary>
/// <param name="light">Directional light source to bet set</param>
/// <param name="index">Index of the directional light source to be set in the shader, in the array of point lights</param>
/// <param name="arrayName">Name of the array containing the directional light data in the shader. Default=["dirLights"].</param>
void UniformProvider::setLight(const SComponent::DirectionalLight& light, int index, std::string arrayName) {
	setUniform(arrayName + "[" + std::to_string(index) + "].intensity", light.intensity);
	setUniform(arrayName + "[" + std::to_string(index) + "].direction", light.direction.normalized());
	setUniform(arrayName + "[" + std::to_string(index) + "].lightMatrix", light.getLightSpaceMatrix());
	if (light.hasShadowMap()) {
		setUniform(arrayName + "[" + std::to_string(index) + "].shadowMap", light.shadowMap->getTextureUnitNum());
	}
}

/// <summary>
/// Same as overload of setLight for directional lights.
/// Sets point light source in the shader. Performs shadow map setting as well if
/// a shadow texture is available on light.
/// </summary>
/// <param name="light">Point light source to bet set</param>
/// <param name="index">Index of the point light source to be set in the shader, in the array of point lights</param>
/// <param name="arrayName">Name of the array containing the point light data in the shader. Defaultt=["dirLights"].</param>
void UniformProvider::setUniform(const SComponent::DirectionalLight& light, int index, std::string arrayName) {
	setLight(light, index, arrayName);
}

/// <summary>
/// Same as overload of setLight for point lights.
/// Sets point light source in the shader. Performs shadow map setting as well if
/// a shadow texture is available on light.
/// </summary>
/// <param name="light">Point light source to bet set</param>
/// <param name="index">Index of the point light source to be set in the shader, in the array of point lights</param>
/// <param name="arrayName">Name of the array containing the point light data in the shader. Default=["pointLights"].</param>
void UniformProvider::setUniform(const SComponent::PointLight& light, int index, std::string arrayName) {
	setLight(light, index, arrayName);
}

//TODO: add setLight for SpotLights

/// <summary>
/// Sets material in the shader.
/// </summary>
/// <param name="material">Material object to be set</param>
/// <param name="index">Index of material to be set in the shader</param>
/// <param name="arrayName">Name of the arra containing the materials in the shader. Default=["materials"].</param>
void UniformProvider::setMaterial(const SComponent::Material& material, int index, std::string arrayName) {
	bool albedo_is_texture;
	if (material.albedo.index() == 0) { //Smath::Vector3

		Smath::Vector3 albedo = std::get<Smath::Vector3>(material.albedo);
		albedo_is_texture = false;

		setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", 0);
		setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", albedo);
	}
	else { //Texture

		Texture2D& albedo = *std::get<std::shared_ptr<Texture2D>>(material.albedo);
		auto textureUnit = albedo.getTextureUnitNum();
		if (textureUnit == -1) {
			//TODO: automatic texture unit creation could be implemented in the future
			Smath::Vector3 albedo(1.0, 0.0, 1.0);
			albedo_is_texture = false;

			setUniform(arrayName + "[" + std::to_string(index) + "].albedoTexture", 0);
			setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", albedo);
		}
		albedo_is_texture = true;
		setUniform(arrayName + "[" + std::to_string(index) + "].albedoVec", Smath::Vector3(0.0, 0.0, 0.0));
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

/// <summary>
/// Same as setMaterial
/// Sets material in the shader.
/// </summary>
/// <param name="material">Material object to be set</param>
/// <param name="index">Index of material to be set in the shader</param>
/// <param name="arrayName">Name of the arra containing the materials in the shader. Default=["materials"].</param>
void UniformProvider::setUniform(const SComponent::Material& material, int index, std::string arrayName) {
	setMaterial(material, index, arrayName);
}