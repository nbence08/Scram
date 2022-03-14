#pragma once
#include <functional>
#include "core/OpenGL/ShaderProgram.h"
#include "core/OpenGL/Framebuffer.h"
#include "main/Logger.h"
#include "rendering/Scene.h"
#include "io/io.h"

enum class PassType {
	preProcess,
	process,
	postProcess
};

/// <summary>
/// class representing a single pass over a scene object
/// </summary>
class Pass {
	std::string shaderName;

	std::shared_ptr<ShaderProgram> program;
	UniformProvider* programUniforms;
	std::shared_ptr<Framebuffer> fbo;

	std::unordered_map<std::string, std::shared_ptr<Texture2D>> texture2DInputs;
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> texture2DOutputs;

	std::unordered_map<std::string, std::shared_ptr<TextureCube>> textureCubeInputs;
	std::unordered_map<std::string, std::shared_ptr<TextureCube>> textureCubeOutputs;

	std::function<void(Mesh&)> passMeshLambda;
	std::function<void(Entity&)> passEntityLambda;
	std::function<void(Scene&)> passSceneLambda;

public:
	/// <summary>
	/// lambda to be called before passing the first Entity
	/// </summary>
	std::function<void(Scene&)> prepareScene;

	/// <summary>
	/// lambda to be called before passing each Entity
	/// </summary>
	std::function<void(Entity&)> prepareEntity;

	/// <summary>
	/// Pointer to a custom object, which can be used to store custom data.
	/// </summary>
	void* object;

	/// <summary>
	/// Callback to be called when the destructor of the pass is invoked.
	/// This callback should be used to properly delete the
	/// custom data store object created in any lambda.
	/// </summary>
	std::function<void()> onDestroy;

	Pass();

	/// <summary>
	/// Creates the pass with the supplied shaderName used to invoke makeShaderProgram,
	/// and the supplied fboInfo used to invoke makeFramebuffer.
	/// </summary>
	/// <param name="shaderName">std::string&</param>
	/// <param name="fboInfo">FboCreateInfo&</param>
	inline Pass(std::string& shaderName, FboCreateInfo& fboInfo):Pass() {
		makeShaderProgram(shaderName);
		makeFramebuffer(fboInfo);
	}
	
	Pass(std::string& shaderName, std::shared_ptr<Framebuffer> fbo);

	~Pass();

	/// <summary>
	/// Reads shader source code with the name supplied as parameter, and creates a shader program
	/// with the shaders. Looks for the shaders in "$(Workspace)shaders/" folder. There must be at
	/// least a vertex and a fragment shader to succeed.
	/// </summary>
	/// <param name="shaderName">Name of the shaders to be used to create the program.</param>
	void makeShaderProgram(std::string& shaderName);

	/// <summary>
	/// Creates a framebuffer for the pass.
	/// </summary>
	/// <param name="fboInfo">Create info for the FBO to be created for the pass.</param>
	void makeFramebuffer(FboCreateInfo& fboInfo);

	/// <summary>
	/// Adds a texture as texture input.
	/// </summary>
	/// <param name="name">Name of the texture input.</param>
	/// <param name="texture">Texture to be added as input.</param>
	void addTextureInput(std::string name, std::shared_ptr<Texture2D> texture);

	/// <summary>
	/// Adds a texture as texture input.
	/// </summary>
	/// <param name="name">Name of the texture input.</param>
	/// <param name="texture">Texture to be added as input.</param>
	void addTextureInput(std::string name, std::shared_ptr<TextureCube> texture);

	/// <summary>
	/// Adds a texture as texture output.
	/// </summary>
	/// <param name="name">Name of the texture output.</param>
	/// <param name="texture">Texture to be added as output.</param>
	void addTextureOutput(std::string name, std::shared_ptr<Texture2D> texture);

	/// <summary>
	/// Adds a texture as texture output.
	/// </summary>
	/// <param name="name">Name of the texture output.</param>
	/// <param name="texture">Texture to be added as output.</param>
	void addTextureOutput(std::string name, std::shared_ptr<TextureCube> texture);
	
	/// <summary>
	/// Returns a shared pointer to the program used by the pass.
	/// </summary>
	/// <returns>std::shared_ptr to ShaderProgram used by the pass</returns>
	inline std::shared_ptr<ShaderProgram> getProgram() { return program; }

	/// <summary>
	/// Returns a shared pointer to the Framebuffer used by the pass.
	/// </summary>
	/// <returns>std::shared_ptr to Framebuffer used by the pass</returns>
	inline std::shared_ptr<Framebuffer> getFbo() { return fbo; }

	/// <summary>
	/// Sets FBO of Pass to the object supplied as parameter.
	/// </summary>
	/// <param name="fbo">std::shared_ptr to object, to which the fbo of the pass will be set</param>
	inline void setFbo(std::shared_ptr<Framebuffer> fbo){ this->fbo = fbo; }

	/// <summary>
	/// Sets ShaderProgram of Pass to the object supplied as parameter.
	/// </summary>
	/// <param name="program">std::shared_ptr to object, to which the ShaderProgram of the pass will be set</param>
	inline void setProgram(std::shared_ptr<ShaderProgram> program) { this->program = program; }

	/// <summary>
	/// Getter for 2D texture inputs
	/// </summary>
	/// <returns>std::unordered_map<std::string, std::shared_ptr<Texture2D>></returns>
	inline auto& get2DTextureInputs() { return texture2DInputs; }

	/// <summary>
	/// Getter for 2D texture outputs
	/// </summary>
	/// <returns>std::unordered_map<std::string, std::shared_ptr<Texture2D>></returns>
	inline auto& get2DTextureOutputs() { return texture2DOutputs; }

	/// <summary>
	/// Getter for cube texture inputs
	/// </summary>
	/// <returns>std::unordered_map<std::string, std::shared_ptr<TextureCube>></returns>
	inline auto& getCubeTextureInputs() { return textureCubeInputs; }
	
	/// <summary>
	/// Getter for cube texture outputs
	/// </summary>
	/// <returns>std::unordered_map<std::string, std::shared_ptr<TextureCube>></returns>
	inline auto& getCubeTextureOutputs() { return textureCubeOutputs; }
	
	/// <summary>
	/// Setter for passMesh method. Note, that the function provided will not be the only
	/// subroutine called, when the passMesh method of the object is invoked. For further info
	/// see passMesh definition.
	/// </summary>
	/// <param name="lambda">passMesh function to be set</param>
	inline void setPassMesh(std::function<void(Mesh&)> lambda) {
		this->passMeshLambda = lambda;
	}

	/// <summary>
	/// Setter for passEntity method. Note, that the function provided will not be the only
	/// subroutine called, when the passEntity method of the object is invoked. For further info
	/// see passEntity definition.
	/// </summary>
	/// <param name="lambda">passEntity function to be set</param>
	inline void setPassEntity(std::function<void(Entity&)> lambda) {
		this->passEntityLambda = lambda;
	}

	/// <summary>
	/// Setter for passScene method. Note, that the function provided will not be the only
	/// subroutine called, when the passScene method of the object is invoked. For further info
	/// see passScene definition.
	/// </summary>
	/// <param name="lambda">passScene function to be set</param>
	inline void setPassScene(std::function<void(Scene&)> lambda) {
		this->passSceneLambda = lambda;
	}
	
	/// <summary>
	/// Executes the pass for the mesh provided as parameter.
	/// </summary>
	/// <param name="mesh"></param>
	void passMesh(Mesh& mesh);

	/// <summary>
	/// Executes the pass for the entity provided as parameter.
	/// </summary>
	/// <param name="entity"></param>
	void passEntity(Entity& entity);

	/// <summary>
	/// Executes the pass for the scene provided as parameter.
	/// </summary>
	/// <param name="scene"></param>
	void passScene(Scene& scene);
};

