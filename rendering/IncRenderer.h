#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "GL/glew.h"
#include "core/OpenGL/VertexArray.h"
#include "core/OpenGL/Buffer.h"
#include "core/OpenGL/ShaderProgram.h"
#include "io/IO.h"
#include "core/CubeData.hpp"
#include "components/PerspectiveCamera.h"
#include "components/Transform.h"
#include "core/math/linear_algebra.hpp"
#include "Scene.h"
#include "core/OpenGL/Framebuffer.h"

#include "core/Global_Props.hpp"

//incremental renderer
class IncRenderer {
	/*
	This could can be used for the occasion, when multiple vbos would be used with a single vao, for the renderer
	It requires some modification, but it could be used in the future

	//mesh uid -> vbo id
	using meshId = uint64_t;

	std::unordered_map<meshId, std::shared_ptr<Buffer>> vbos;
	std::unordered_map<meshId, std::shared_ptr<Buffer>> ebos;

	void loadMeshVertices(Mesh& mesh);

	void loadMeshIndices(Mesh& mesh);
	*/

	void setMeshUniforms(std::shared_ptr<Mesh> mesh, std::shared_ptr<Entity> model);

	void setProcessMeshModelMatrix(std::shared_ptr<Mesh> mesh, std::shared_ptr<Entity> model);

	void setMeshMaterial(std::shared_ptr<Mesh> mesh);



	ShaderProgram processProgram;
	UniformProvider* processUniforms;

	UniformProvider* shadowUniforms;
	Framebuffer shadowBuffer;
	ShaderProgram shadowProgram;

	ShaderProgram quadProgram;
	UniformProvider* quadUniforms;

public:
	IncRenderer(std::string defaultShaderName = "shaders/incremental");

	void setCullFace(bool cullFace);

	void draw(Scene& scene);
};

