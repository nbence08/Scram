#pragma once

#include "rendering_export.hpp"

#include <functional>

#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"
#include "Logger.hpp"
#include "Scene.hpp"

namespace ScOpenGL{
	class Texture2D;
	class TextureCube;
}

namespace SComponent{
	class Mesh;
	class Entity;
}

struct ShaderSources {
	std::string vertex;
	std::string fragment;
	std::string geometry;
	std::string compute;
};

namespace ScRendering {
	enum class PassType {
		preProcess,
		process,
		postProcess
	};

	/// <summary>
	/// class representing a single pass over a scene object
	/// </summary>
	class RENDERING_EXPORT Pass {
		std::string shaderName;

		std::shared_ptr<ScOpenGL::ShaderProgram> program;
		ScOpenGL::UniformProvider* programUniforms;
		std::shared_ptr<ScOpenGL::Framebuffer> fbo;

		std::unordered_map<std::string, std::shared_ptr<ScOpenGL::Texture2D>> texture2DInputs;
		std::unordered_map<std::string, std::shared_ptr<ScOpenGL::Texture2D>> texture2DOutputs;

		std::unordered_map<std::string, std::shared_ptr<ScOpenGL::TextureCube>> textureCubeInputs;
		std::unordered_map<std::string, std::shared_ptr<ScOpenGL::TextureCube>> textureCubeOutputs;

		std::function<void(SComponent::Mesh&)> passMeshLambda;
		std::function<void(SComponent::Entity&)> passEntityLambda;
		std::function<void(Scene&)> passSceneLambda;

	public:

		/// lambda to be called before passing the first Entity
		std::function<void(Scene&)> prepareScene;

		/// lambda to be called before passing each Entity
		std::function<void(SComponent::Entity&)> prepareEntity;

		/// Pointer to a custom object, which can be used to store custom data.
		void* object;

		/// Callback to be called when the destructor of the pass is invoked.
		/// This callback should be used to properly delete the
		/// custom data store object created in any lambda.
		std::function<void()> onDestroy;

		Pass();

		/// Creates the pass with the supplied shaderName used to invoke makeShaderProgram,
		/// and the supplied fboInfo used to invoke makeFramebuffer.
		inline Pass(const ShaderSources& sources, ScOpenGL::FboCreateInfo& fboInfo) :Pass() {
			makeShaderProgram(sources);
			makeFramebuffer(fboInfo);
		}


		Pass(const ShaderSources& sources, std::shared_ptr<ScOpenGL::Framebuffer> fbo);

		~Pass();

		/// Reads shader source code with the name supplied as parameter, and creates a shader program
		/// with the shaders. Looks for the shaders in "$(Workspace)shaders/" folder. There must be at
		/// least a vertex and a fragment shader to succeed.
		void makeShaderProgram(const ShaderSources& sources);

		/// <summary>
		/// Creates a framebuffer for the pass.
		/// </summary>
		/// <param name="fboInfo">Create info for the FBO to be created for the pass.</param>
		void makeFramebuffer(ScOpenGL::FboCreateInfo& fboInfo);
		void addTextureInput(const std::string& name, std::shared_ptr<ScOpenGL::Texture2D> texture);
		void addTextureInput(const std::string& name, std::shared_ptr<ScOpenGL::TextureCube> texture);
		void addTextureOutput(const std::string& name, std::shared_ptr<ScOpenGL::Texture2D> texture);
		void addTextureOutput(const std::string& name, std::shared_ptr<ScOpenGL::TextureCube> texture);

		/// Returns a shared pointer to the program used by the pass.
		inline std::shared_ptr<ScOpenGL::ShaderProgram> getProgram() { return program; }

		/// Returns a shared pointer to the Framebuffer used by the pass.
		inline std::shared_ptr<ScOpenGL::Framebuffer> getFbo() { return fbo; }
		inline void setFbo(std::shared_ptr<ScOpenGL::Framebuffer> fbo) { this->fbo = fbo; }
		inline void setProgram(std::shared_ptr<ScOpenGL::ShaderProgram> program) { this->program = program; }
		inline auto& get2DTextureInputs() { return texture2DInputs; }
		inline auto& get2DTextureOutputs() { return texture2DOutputs; }
		inline auto& getCubeTextureInputs() { return textureCubeInputs; }
		inline auto& getCubeTextureOutputs() { return textureCubeOutputs; }

		/// Setter for passMesh method. Note, that the function provided will not be the only
		/// subroutine called, when the passMesh method of the object is invoked. For further info
		/// see passMesh definition.
		inline void setPassMesh(std::function<void(SComponent::Mesh&)> lambda) {
			this->passMeshLambda = lambda;
		}

		/// Setter for passEntity method. Note, that the function provided will not be the only
		/// subroutine called, when the passEntity method of the object is invoked. For further info
		/// see passEntity definition.
		inline void setPassEntity(std::function<void(SComponent::Entity&)> lambda) {
			this->passEntityLambda = lambda;
		}

		/// Setter for passScene method. Note, that the function provided will not be the only
		/// subroutine called, when the passScene method of the object is invoked. For further info
		/// see passScene definition.
		inline void setPassScene(std::function<void(Scene&)> lambda) {
			this->passSceneLambda = lambda;
		}

		/// Executes the pass for the mesh provided as parameter.
		void passMesh(SComponent::Mesh& mesh);

		/// Executes the pass for the entity provided as parameter.
		void passEntity(SComponent::Entity& entity);

		/// Executes the pass for the scene provided as parameter.
		void passScene(Scene& scene);

		void setLight(const SComponent::PointLight& light, int index, std::string arrayName = "pointLights");

		void setLight(const SComponent::DirectionalLight& light, int index, std::string arrayName = "dirLights");

		//TODO: add setLight for SpotLights

		void setMaterial(const SComponent::Material& material, int index, std::string arrayName = "materials");
	};
}
