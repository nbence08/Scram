#pragma once
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <stack>
#include <variant>

#include "Struct_Definitions.hpp"

namespace ScOpenGL {

	void clearTextureUnits();

	class Texture2D;
	class TextureCube;

	class TextureUnit;

	/// <summary>
	/// Class representing an OpenGL texture unit 
	/// </summary>
	class TextureUnit {
	public:
		TextureUnit(const TextureUnit& other) = delete;
		TextureUnit& operator=(const TextureUnit& other) = delete;
		~TextureUnit();
		static std::shared_ptr<TextureUnit> getNewInstance();

		void bind();
		static void unbind();

		template <typename T>
		void bindTexture(std::shared_ptr<T> tex);
		void unbindTexture();
		void loadTexture(const ImageData2D& d);
		void loadTexture(const ImageDataCube& d);

		int getUnitNum() const;

		template <typename T>
		bool doesBoundTextureMatch(T* tex);
		bool hasBoundTexture();
		bool isBoundTextureEmpty();
	private:
		unsigned int unitNum;

		std::variant<std::shared_ptr<Texture2D>, std::shared_ptr<TextureCube>> boundTexture;

		void hollowBind();
		void hollowUnbind();
		void initTexture(const Texture2D& tex);
		TextureUnit(int unitNum);

		friend class Texture2D;
	};

}