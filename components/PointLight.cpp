#include "PointLight.hpp"
#include "TextureUnit.hpp"
#include "Struct_Definitions.hpp"

namespace SComponent {
	PointLight::PointLight() {
		farPlane = global::shadowProjEdgeSize;

		shadowMap = std::make_shared<ScOpenGL::TextureCube>();
		auto texUnit = ScOpenGL::TextureUnit::getNewInstance();

		texUnit->bind();
		texUnit->bindTexture(shadowMap);

		ImageDataCube allocData;
		allocData.format = GL_DEPTH_COMPONENT;
		allocData.internalFormat = GL_DEPTH_COMPONENT;
		allocData.size = global::shadowWidth;
		allocData.level = 0;
		allocData.type = GL_FLOAT;
		for (int i = 0; i < 6; i++) allocData.pixels[i] = nullptr;

		texUnit->loadTexture(allocData);

		texUnit->unbindTexture();
		texUnit->unbind();
	}

	std::vector<ScMath::Matrix4> PointLight::getLightSpaceMatrices() const {
		auto proj = math::perspective(90.0, 1.0, 1.0, farPlane);
		auto rightward = math::getLookAt(ScMath::Vector3(1.0, 0.0, 0.0), ScMath::Vector3(0.0, -1.0, 0.0), position);
		auto leftward = math::getLookAt(ScMath::Vector3(-1.0, 0.0, 0.0), ScMath::Vector3(0.0, -1.0, 0.0), position);

		auto upward = math::getLookAt(ScMath::Vector3(0.0, 1.0, 0.0), ScMath::Vector3(0.0, 0.0, 1.0), position);
		auto downward = math::getLookAt(ScMath::Vector3(0.0, -1.0, 0.0), ScMath::Vector3(0.0, 0.0, -1.0), position);

		auto backward = math::getLookAt(ScMath::Vector3(0.0, 0.0, 1.0), ScMath::Vector3(0.0, -1.0, 0.0), position);
		auto forward = math::getLookAt(ScMath::Vector3(0.0, 0.0, -1.0), ScMath::Vector3(0.0, -1.0, 0.0), position);

		std::shared_ptr<ScOpenGL::TextureCube> shadowMap;

		std::vector<ScMath::Matrix4> matrices;

		matrices.reserve(6);

		matrices.emplace_back(proj * rightward);
		matrices.emplace_back(proj * leftward);

		matrices.emplace_back(proj * upward);
		matrices.emplace_back(proj * downward);

		matrices.emplace_back(proj * backward);
		matrices.emplace_back(proj * forward);

		return matrices;
	}
}
