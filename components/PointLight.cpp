#include "PointLight.h"

PointLight::PointLight() {
	farPlane = global::shadowProjEdgeSize;

	shadowMap = std::make_shared<TextureCube>();
	auto texUnit = TextureUnit::getNewInstance();

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

std::vector<SMath::Matrix4> PointLight::getLightSpaceMatrices() const {
	auto proj = SMath::perspective(90.0, 1.0, 1.0, farPlane);
	auto rightward = SMath::getLookAt(SMath::Vector3(1.0, 0.0, 0.0), SMath::Vector3(0.0, -1.0, 0.0), position);
	auto leftward = SMath::getLookAt(SMath::Vector3(-1.0, 0.0, 0.0), SMath::Vector3(0.0, -1.0, 0.0), position);

	auto upward = SMath::getLookAt(SMath::Vector3(0.0, 1.0, 0.0), SMath::Vector3(0.0, 0.0, 1.0), position);
	auto downward = SMath::getLookAt(SMath::Vector3(0.0, -1.0, 0.0), SMath::Vector3(0.0, 0.0, -1.0), position);

	auto backward = SMath::getLookAt(SMath::Vector3(0.0, 0.0, 1.0), SMath::Vector3(0.0, -1.0, 0.0), position);
	auto forward = SMath::getLookAt(SMath::Vector3(0.0, 0.0, -1.0), SMath::Vector3(0.0, -1.0, 0.0), position);

	std::shared_ptr<TextureCube> shadowMap;

	std::vector<SMath::Matrix4> matrices;

	matrices.reserve(6);

	matrices.emplace_back(proj * rightward);
	matrices.emplace_back(proj * leftward);

	matrices.emplace_back(proj * upward);
	matrices.emplace_back(proj * downward);

	matrices.emplace_back(proj * backward);
	matrices.emplace_back(proj * forward);

	return matrices;
}