#pragma once
#include <vector>

#include "core/OpenGL/Texture2D.h"
#include "core/math/linear_algebra.hpp"
#include "core/OpenGL/VertexArray.h"
#include "core/OpenGL/Buffer.h"
#include "ComponentBase.hpp"

struct Vertex {
	Smath::Vector3 position;
	Smath::Vector3 normal;
	Smath::Vector2 texCoord;
};

static uint64_t topMeshId = 0;

class Mesh : public ComponentBase{

	VertexArray vao;
	Buffer vbo;
	Buffer ebo;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:

	const uint64_t uid;

	inline Mesh():uid(topMeshId++) { 
		vao = (VertexArray());
		vbo = (Buffer());
		ebo = (Buffer());

		vao.addReal(3);
		vao.addReal(3);
		vao.addReal(2);

		vao.bindVertexBuffer(vbo);
		vao.bindIndexBuffer(ebo);
	}

	inline std::vector<Vertex>& getVertices() { return vertices; }
	inline std::vector<unsigned int>& getIndices(){ return indices; }

	inline void setIndices(std::vector<unsigned int>& indices) { this->indices = indices; }
	inline void setIndices(std::vector<unsigned int>&& indices) { this->indices = indices; }

	inline VertexArray& getVao() { return vao; }
	inline Buffer& getVbo() { return vbo; }
	inline Buffer& getEbo() { return ebo; }

	void bufferVertices() {
		vbo.bufferData(&vertices.data()[0], sizeof(Vertex) * vertices.size());
		vao.attributePointer();
	}

	void bufferIndices() {
		ebo.bufferData(&indices.data()[0], sizeof(unsigned int)*indices.size());
	}
};

