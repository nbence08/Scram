#include "DirectionalLight.h"
#include "glm/matrix.hpp"
#include "core/Global_Props.hpp"

SMath::Matrix4 DirectionalLight::getLightSpaceMatrix() const {

	auto normDir = direction.normalized();
	SMath::Vector3 up;
	if (normDir.x == 0 && normDir.y == 1 && normDir.z == 0) {
		up = SMath::Vector3(0, 0, 1);
	}
	else if (normDir.x == 0 && normDir.y == -1 && normDir.z == 0) {
		up = SMath::Vector3(0, 0, -1);
	}
	else {
		up = SMath::Vector3(0, 1, 0);
	}

	auto right = cross(-up, -normDir);
	auto trueUp = cross(right, -normDir);

	float edgeRight = (float)global::screenWidth/4;
	float edgeTop = (float)global::screenHeight/4;

	SMath::Matrix4 mat4_1 = math::orthographic(-edgeRight, edgeRight, edgeTop, -edgeTop, 1.0, 500);
	//ideally position for the getLookAt would be ahead of the position of the camera, in its direction
	SMath::Matrix4 mat4_2 = math::getLookAt(-normDir, trueUp, normDir * ORTHOGONAL_EDGE_SIZE/2);

	return mat4_1 * mat4_2;
}

DirectionalLight::DirectionalLight() {
	shadowMap = std::make_shared<Texture2D>();
	auto texUnit = TextureUnit::getNewInstance();

	texUnit->bind();
	texUnit->bindTexture(shadowMap);

	ImageData2D allocData;
	allocData.format = GL_DEPTH_COMPONENT;
	allocData.internalFormat = GL_DEPTH_COMPONENT;
	allocData.width = global::screenWidth;
	allocData.height = global::screenHeight;
	allocData.level = 0;
	allocData.type = GL_UNSIGNED_BYTE;
	allocData.pixels = nullptr;

	texUnit->loadTexture(allocData);

	texUnit->unbindTexture();
	texUnit->unbind();

}
