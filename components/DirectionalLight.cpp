#include "DirectionalLight.hpp"
#include "glm/matrix.hpp"
#include "Global_Props.hpp"

#include "struct_definitions.hpp"
#include "TextureUnit.hpp"

namespace SComponent {
	Smath::Matrix4 DirectionalLight::getLightSpaceMatrix() const {

		auto normDir = direction.normalized();
		Smath::Vector3 up;
		if (normDir.x == 0 && normDir.y == 1 && normDir.z == 0) {
			up = Smath::Vector3(0, 0, 1);
		}
		else if (normDir.x == 0 && normDir.y == -1 && normDir.z == 0) {
			up = Smath::Vector3(0, 0, -1);
		}
		else {
			up = Smath::Vector3(0, 1, 0);
		}

		auto right = cross(-up, -normDir);
		auto trueUp = cross(right, -normDir);

		float edgeRight = (float)global::shadowProjEdgeSize / 1.5f;
		float edgeTop = (float)global::shadowProjEdgeSize / 1.5f;

		Smath::Matrix4 mat4_1 = math::orthographic(-edgeRight, edgeRight, edgeTop, -edgeTop, 1.0, 500);
		//ideally position for the getLookAt would be ahead of the position of the camera, in its direction
		Smath::Matrix4 mat4_2 = math::getLookAt(-normDir, trueUp, normDir * global::shadowProjEdgeSize);

		return mat4_1 * mat4_2;
	}

	DirectionalLight::DirectionalLight() {
		shadowMap = std::make_shared<ScOpenGL::Texture2D>();
		auto texUnit = ScOpenGL::TextureUnit::getNewInstance();

		texUnit->bind();
		texUnit->bindTexture(shadowMap);

		ImageData2D allocData;
		allocData.format = GL_DEPTH_COMPONENT;
		allocData.internalFormat = GL_DEPTH_COMPONENT;
		allocData.width = global::shadowWidth;
		allocData.height = global::shadowHeight;
		allocData.level = 0;
		allocData.type = GL_UNSIGNED_BYTE;
		allocData.pixels = nullptr;

		texUnit->loadTexture(allocData);

		texUnit->unbindTexture();
		texUnit->unbind();

	}
}
