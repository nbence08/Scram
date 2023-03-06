#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <set>
#include <stdexcept>
#include "Buffer.hpp"
#include "VertexAttribManager.hpp"
#include <memory>

#include "GPU_export.hpp"

namespace ScOpenGL {

	class Buffer;
	class VertexAttribManager;

	static unsigned int boundArray = 0;

	static bool isValidBufferType(GLenum bufferType);

	class GPU_EXPORT VertexArray {
		using BufferIndex_t = unsigned int;

		unsigned int id;
		std::unordered_map<GLenum, Buffer*> boundBuffers;
		std::unordered_map<BufferIndex_t, Buffer*> vertexBuffers;
		std::shared_ptr<VertexAttribManager> vam;

		void hollowBind() const;

		void hollowUnbind() const;

		void unbindBuffer(GLenum bufferType);

		void bindBuffer(Buffer& buffer, GLenum bufferType);

		bool boundBuffersHasBufferType(GLenum bufferType);

		auto findVertexBuffer(Buffer& buffer);

		friend Buffer;
		friend VertexAttribManager;

	public:
		VertexArray(const VertexArray& vao) = delete;
		VertexArray& operator=(const VertexArray& vao) = delete;

		VertexArray(VertexArray&& vao) noexcept;
		VertexArray& operator=(VertexArray&& vao) noexcept;

		VertexArray();
		~VertexArray();

		void bind();

		static void unbind();

		inline unsigned int getId() { return id; }


		void bindIndexBuffer(Buffer& buffer);
		void bindVertexBuffer(Buffer& buffer, unsigned int bufferIndex = 0);
		void unbindVertexBuffer(Buffer& buffer);

		void addReal(unsigned int size, unsigned int bufferIndex = 0);
		void attributeFormat();
		void attributeBinding();
		void attributePointer();

	};

}
