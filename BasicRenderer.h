#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ConstantHolder.h"
#include "OpenGlOperations.hpp"

#include "Renderer.h"
#include "Shader.h"
#include "ScreenSize.h"
#include "VertexBufferObject.h"

//TODO: decide whether or not to be placed in its own header
struct RenderUnit {
    unsigned int fbo;
    unsigned int colorBufTex;
    unsigned int rbo;
    unsigned int vao;
    unsigned int vbo;
};

class BasicRenderer: public Renderer {

private:
	std::shared_ptr<Camera> camera;
    std::shared_ptr<Shader> baseShader;
    std::shared_ptr<Shader> postProcessorShader;

    RenderUnit colorRenderUnit;
    RenderUnit screenRenderUnit;

    unsigned int width, height;
    float gamma;
    unsigned int frameWidth;
    unsigned int frameHeight;

public:
	inline void setCamera(std::shared_ptr<Camera> camera) override {
       camera = camera;
	}

	BasicRenderer(std::shared_ptr<Camera> cam, ScreenSize scSize, float gamma = 2.2f) {
        camera = cam;
        Shader baseShaderobj("shaders/basic.vert", "shaders/basic.frag");
        baseShader = std::make_shared<Shader>(baseShaderobj);

        Shader postProcessorShaderobj("shaders/postProcessor.vert", "shaders/postProcessor.frag");
        postProcessorShader = std::make_shared<Shader>(postProcessorShaderobj);

        setGamma(gamma);
        postProcessorShader->uniforms().uniform(std::string("samples"), (int)ConstantHolder::samples);
        postProcessorShader->uniforms().uniform(std::string("recSamples"), 1.0f/(float)ConstantHolder::samples);

        setScreenSize(scSize.width, scSize.height);

        //{fbo, colorBuffer, rbo, vao}
        colorRenderUnit = createFramebuffer();
        glGenVertexArrays(1, &colorRenderUnit.vao);
        glBindVertexArray(colorRenderUnit.vao);

        glGenBuffers(1, &colorRenderUnit.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorRenderUnit.vbo);


        //TODO: replace with VertexBufferObject
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

        glBufferData(GL_ARRAY_BUFFER, sizeof(ConstantHolder::cube), &ConstantHolder::cube, GL_STATIC_DRAW);



        screenRenderUnit.fbo = 0;
        glGenVertexArrays(1, &screenRenderUnit.vao);
        glBindVertexArray(screenRenderUnit.vao);

        glGenBuffers(1, &screenRenderUnit.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, screenRenderUnit.vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, NULL);
        glEnableVertexAttribArray(0);

        glBufferData(GL_ARRAY_BUFFER, sizeof(ConstantHolder::square), ConstantHolder::square, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    ~BasicRenderer() {
        glDeleteVertexArrays(1, &colorRenderUnit.vao);
        glDeleteBuffers(1, &colorRenderUnit.vbo);
        glDeleteTextures(1, &colorRenderUnit.colorBufTex);
        glDeleteFramebuffers(1, &colorRenderUnit.fbo);
        glDeleteRenderbuffers(1, &colorRenderUnit.rbo);

        glDeleteBuffers(1, &screenRenderUnit.vbo);
    }

    void setGamma(float gamma) {
        this->gamma = gamma;
        postProcessorShader->uniforms().uniform(std::string("recGamma"), 1.0f / gamma);
    }

    void setScreenSize(unsigned int width, unsigned int height) override {
        this->width = width;
        this->height = height;

        frameWidth = 1.4 * width;
        frameHeight = 1.4 * height;

        postProcessorShader->uniforms().uniform(std::string("size"), glm::vec2(frameWidth, frameHeight));
    }

public: void render() override {
    baseShader->use();

    glClearColor(0.03f, 0.03f, 0.22f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glViewport(0, 0, frameWidth, frameHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, colorRenderUnit.fbo);
    glBindVertexArray(colorRenderUnit.vao);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    baseShader->uniforms().uniform(std::string("view"), camera->view());
    baseShader->uniforms().uniform(std::string("proj"), camera->proj());

    glDrawArrays(GL_TRIANGLES, 0, 36);

    // DELIMITER

    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, screenRenderUnit.fbo);
    glBindVertexArray(screenRenderUnit.vao);

    postProcessorShader->use();
    postProcessorShader->uniforms().uniform(std::string("barrelStrength"), 10000.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorRenderUnit.colorBufTex);

    postProcessorShader->uniforms().uniform(std::string("tex"), 0);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT);


    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    

    glBindVertexArray(0);
}

RenderUnit createFramebuffer() {
    
    
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    unsigned int colorBuffer;
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorBuffer);

    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, ConstantHolder::samples, GL_RGBA, (int)frameWidth, (int)frameHeight, GL_TRUE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorBuffer, 0);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, ConstantHolder::samples, GL_DEPTH24_STENCIL8, frameWidth, frameHeight);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fboStatus != GL_FRAMEBUFFER_COMPLETE) std::cout << "framebuffer not complete" << std::endl;
    return {fbo, colorBuffer, rbo};

}

};

