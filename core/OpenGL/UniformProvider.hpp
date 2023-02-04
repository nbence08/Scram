#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "GL/glew.h"
#include "core/math/linear_algebra.hpp"
#include "TextureUnit.hpp"
#include "components/PointLight.hpp"
#include "components/DirectionalLight.hpp"
#include "components/Material.hpp"
#include "main/Logger.hpp"

class UniformProvider{
	std::unordered_map<std::string, unsigned int> locationCache;
	
	/*std::unordered_map<std::string,
		std::variant<float, double, int, Vector2, Vector3, Vector4, Matrix3, Matrix4>
	> valueCache;*/
	
	unsigned int programId;


	/// <summary>
	/// Gets the location identifier of a uniform variable in the shader 
	/// with name supplied as parameter. It caches the locations of the uniforms.
	/// </summary>
	/// <param name="name">Name of the uniform in the shader, whose location is to be queried</param>
	/// <returns>Location identifier of the uniform</returns>
	unsigned int getUniformLocation(std::string name);
public:
	inline UniformProvider() { programId = 0; }
	inline UniformProvider(unsigned int programId):programId(programId) {}

	/// <summary>
	/// Sets bool uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">bool value set as uniform</param>
	void setUniform(std::string name, bool value);

	/// <summary>
	/// Sets float uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">float value set as uniform</param>
	void setUniform(std::string name, float value);

	/// <summary>
	/// Sets double uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">double value set as uniform</param>
	void setUniform(std::string name, double value);

	/// <summary>
	/// Sets vec2 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="x">real value set as first coordinate of vec2 uniform</param>
	/// <param name="y">real value set as second coordinate of vec2 uniform</param>
	void setUniform(std::string name, const real_t x, const real_t y);

	/// <summary>
	/// Sets vec3 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to. Uses float or double version of glUniform,
	/// based on the preprocessor configuration
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">Vector3 value set as uniform</param>
	void setUniform(std::string name, const Vector3& value);

	/// <summary>
	/// Sets vec4 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to. Uses float or double version of glUniform,
	/// based on the preprocessor configuration
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">Vector4 value set as uniform</param>
	void setUniform(std::string name, const Vector4& value);

	/// <summary>
	/// Sets mat4 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to. Uses float or double version of glUniform,
	/// based on the preprocessor configuration
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">Matrix4 value set as uniform</param>
	void setUniform(std::string name, const Matrix4& value);

	/// <summary>
	/// Sets int uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to.
	/// </summary>
	/// <param name="name">Name of the uniform variable in the shader</param>
	/// <param name="value">int value set as uniform</param>
	void setUniform(std::string name, const int value);

	/// <summary>
	/// Sets texture unit value, identified by the name specified as parameter, in the 
	/// shader program it is attached to.
	/// </summary>
	/// <param name="name">Name of the sampler in the shader</param>
	/// <param name="unit">Id of the texture unit to be set</param>
	void setTexture(std::string samplerName, const TextureUnit& unit);

	/// <summary>
	/// Sets point light source in the shader. Performs shadow map setting as well if
	/// a shadow texture is available on light.
	/// </summary>
	/// <param name="light">Point light source to bet set</param>
	/// <param name="index">Index of the point light source to be set in the shader, in the array of point lights</param>
	/// <param name="arrayName">Name of the array containing the point light data in the shader</param>
	void setLight(const PointLight& light, int index, std::string arrayName = "pointLights");

	/// <summary>
	/// Sets directional light source in the shader. Performs shadow map setting as well if
	/// a shadow texture is available on light.
	/// </summary>
	/// <param name="light">Directional light source to bet set</param>
	/// <param name="index">Index of the directional light source to be set in the shader, in the array of point lights</param>
	/// <param name="arrayName">Name of the array containing the directional light data in the shader</param>
	void setLight(const DirectionalLight& light, int index, std::string arrayName = "dirLights");

	/// <summary>
	/// Same as overload of setLight for directional lights.
	/// Sets point light source in the shader. Performs shadow map setting as well if
	/// a shadow texture is available on light.
	/// </summary>
	/// <param name="light">Point light source to bet set</param>
	/// <param name="index">Index of the point light source to be set in the shader, in the array of point lights</param>
	/// <param name="arrayName">Name of the array containing the point light data in the shader</param>
	void setUniform(const DirectionalLight& light, int index, std::string arrayName = "dirLights");

	/// <summary>
	/// Same as overload of setLight for point lights.
	/// Sets point light source in the shader. Performs shadow map setting as well if
	/// a shadow texture is available on light.
	/// </summary>
	/// <param name="light">Point light source to bet set</param>
	/// <param name="index">Index of the point light source to be set in the shader, in the array of point lights</param>
	/// <param name="arrayName">Name of the array containing the point light data in the shader</param>
	void setUniform(const PointLight& light, int index, std::string arrayName = "pointLights");

	//TODO: add setLight for SpotLights

	/// <summary>
	/// Sets material in the shader.
	/// </summary>
	/// <param name="material">Material object to be set</param>
	/// <param name="index">Index of material to be set in the shader</param>
	/// <param name="arrayName">Name of the arra containing the materials in the shader.</param>
	void setMaterial(const Material& material,int index, std::string arrayName = "materials");

	/// <summary>
	/// Same as setMaterial
	/// Sets material in the shader.
	/// </summary>
	/// <param name="material">Material object to be set</param>
	/// <param name="index">Index of material to be set in the shader</param>
	/// <param name="arrayName">Name of the arra containing the materials in the shader.</param>
	void setUniform(const Material& material, int index, std::string arrayName = "materials");
};

