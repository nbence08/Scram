#pragma once
#include <vector>

#include "core/OpenGL/Texture2D.h"
#include "CTMaterial.h"
#include "core/math/linear_algebra.hpp"
#include "Model.h"
#include "core/OpenGL/VertexArray.h"
#include "core/OpenGL/Buffer.h"

struct Vertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
};

static uint64_t topMeshId = 0;

class Mesh{

	VertexArray vao;
	Buffer vbo;
	Buffer ebo;

	Matrix4 model;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//uid for identifying mesh to renderers
	CTMaterial material;
	
	friend class Model;
public:

	const uint64_t uid;

	inline Mesh():uid(topMeshId++) { 
		vao = (VertexArray());
		vbo = (Buffer());
		ebo = (Buffer());

		model = math::diag4(1.0f);
		vao.bindArrayBuffer(vbo);
		vao.bindIndexBuffer(ebo);
	}

	inline std::vector<Vertex>& getVertices() { return vertices; }
	inline CTMaterial& getMaterial() { return material; }
	inline std::vector<unsigned int>& getIndices(){ return indices; }
	inline Matrix4 getModel(){ return model; }

	inline void setIndices(std::vector<unsigned int>& indices) { this->indices = indices; }
	inline void setIndices(std::vector<unsigned int>&& indices) { this->indices = indices; }

	inline VertexArray& getVao() { return vao; }
	inline Buffer& getVbo() { return vbo; }
	inline Buffer& getEbo() { return ebo; }

	void bufferVertices() {
		vao.bind();
		vao.addReal(3);
		vao.addReal(3);
		vao.addReal(2);

		vbo.bufferData(&vertices.data()[0], sizeof(Vertex) * vertices.size());
		vao.attributePointer();
		vao.unbind();
	}

	void bufferIndices() {
		vao.bind();
		ebo.bufferData(&indices.data()[0], sizeof(unsigned int)*indices.size());
		vao.unbind();
	}
};

