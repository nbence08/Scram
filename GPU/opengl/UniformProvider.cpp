#include "UniformProvider.hpp"

#include "linear_algebra.hpp"
#include "TextureUnit.hpp"
#include "Logger.hpp"

namespace ScOpenGL {

	/// Gets the location identifier of a uniform variable in the shader 
	/// with name supplied as parameter. It caches the locations of the uniforms.
	/// It uses the class member locationCache, which is an std::unordered_map<std::string, unsigned int>
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

	/// Sets bool uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	void UniformProvider::setUniform(std::string name, bool value) {
		setUniform(name, (int)value);
	}

	/// Sets float uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	void UniformProvider::setUniform(std::string name, float value) {
		unsigned int location = getUniformLocation(name);

		glUniform1f(location, value);
	}

	/// Sets double uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	void UniformProvider::setUniform(std::string name, double value) {
		unsigned int location = getUniformLocation(name);

		glUniform1d(location, value);
	}

	/// Sets vec2 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to
	void UniformProvider::setUniform(std::string name, const real_t x, const real_t y) {
		unsigned int location = getUniformLocation(name);
		if (GL_REAL == GL_FLOAT) {
			glUniform2f(location, x, y);
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniform2d(location, x, y);
		}
	}

	/// Sets vec3 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to. Uses float or double version of glUniform,
	/// based on the preprocessor configuration
	void UniformProvider::setUniform(std::string name, const ScMath::Vector3& value) {
		unsigned int location = getUniformLocation(name);
		if (GL_REAL == GL_FLOAT) {
			glUniform3f(location, value.x, value.y, value.z);
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniform3d(location, value.x, value.y, value.z);
		}
	}

	/// Sets vec4 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to. Uses float or double version of glUniform,
	/// based on the preprocessor configuration
	void UniformProvider::setUniform(std::string name, const ScMath::Vector4& value) {
		unsigned int location = getUniformLocation(name);
		if (GL_REAL == GL_FLOAT) {
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniform4d(location, value.x, value.y, value.z, value.w);
		}
	}

	/// Sets mat4 uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to. Uses float or double version of glUniform,
	/// based on the preprocessor configuration
	void UniformProvider::setUniform(std::string name, const ScMath::Matrix4& value) {
		unsigned int location = getUniformLocation(name);

		if (GL_REAL == GL_FLOAT) {
			glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value));
		}
		else if (GL_REAL == GL_DOUBLE) {
			glUniformMatrix4dv(location, 1, GL_FALSE, reinterpret_cast<const GLdouble*>(&value));
		}
	}

	/// Sets int uniform value, identified by the name specified as parameter, in the 
	/// shader program it is attached to.
	void UniformProvider::setUniform(std::string name, const int value) {
		unsigned int location = getUniformLocation(name);

		glUniform1i(location, value);
	}

	/// Sets texture unit value, identified by the name specified as parameter, in the 
	/// shader program it is attached to.
	void UniformProvider::setTexture(std::string samplerName, const TextureUnit& unit) {
		unsigned int location = getUniformLocation(samplerName);

		glUniform1i(location, unit.getUnitNum());
	}
}