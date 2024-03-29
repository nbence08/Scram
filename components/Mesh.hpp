#pragma once
#include <vector>

#include "Texture2D.hpp"
#include "linear_algebra.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "ComponentBase.hpp"

#include "components_export.hpp"

namespace SComponent {
	struct Vertex {
		ScMath::Vector3 position;
		ScMath::Vector3 normal;
		ScMath::Vector2 texCoord;
	};

	static uint64_t topMeshId = 0;

	class COMPONENTS_EXPORT Mesh : public ComponentBase {

		ScOpenGL::VertexArray vao;
		ScOpenGL::Buffer vbo;
		ScOpenGL::Buffer ebo;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

	public:

		const uint64_t uid;

		inline Mesh() :uid(topMeshId++) {
			vao = (ScOpenGL::VertexArray());
			vbo = (ScOpenGL::Buffer());
			ebo = (ScOpenGL::Buffer());

			vao.addReal(3);
			vao.addReal(3);
			vao.addReal(2);

			vao.bindVertexBuffer(vbo);
			vao.bindIndexBuffer(ebo);
		}

		inline std::vector<Vertex>& getVertices() { return vertices; }
		inline std::vector<unsigned int>& getIndices() { return indices; }

		inline void setIndices(std::vector<unsigned int>& indices) { this->indices = indices; }
		inline void setIndices(std::vector<unsigned int>&& indices) { this->indices = indices; }

		inline ScOpenGL::VertexArray& getVao() { return vao; }
		inline ScOpenGL::Buffer& getVbo() { return vbo; }
		inline ScOpenGL::Buffer& getEbo() { return ebo; }

		void bufferVertices() {
			vbo.bufferData(&vertices.data()[0], sizeof(Vertex) * vertices.size());
			vao.attributePointer();
		}

		void bufferIndices() {
			ebo.bufferData(&indices.data()[0], sizeof(unsigned int) * indices.size());
		}
	};
}
