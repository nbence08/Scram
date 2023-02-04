#version 440

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tc;

struct DirectionalLight{
	vec3 intensity;
	vec3 direction;
	sampler2D shadowMap;
	mat4 lightMatrix;
};

const int dirLightsLen = 1;

uniform DirectionalLight dirLights[dirLightsLen];
uniform int lightIndex;
uniform mat4 model;

void main(){
	gl_Position = (dirLights[lightIndex].lightMatrix*model*vec4(pos, 1.0));
}
