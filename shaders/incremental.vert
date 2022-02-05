#version 440

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTex;


struct DirectionalLight{
	vec3 intensity;
	vec3 direction;
	sampler2D shadowMap;
	mat4 lightMatrix;
};

const int dirLightsLen = 1;
uniform DirectionalLight dirLights[dirLightsLen];

out vec3 fNormal;
out vec3 fragPos;
out vec2 fTex;
out vec4 lightSpacePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fragPos = (model * vec4(vPos, 1.0)).xyz;
	gl_Position = projection*view*vec4(fragPos, 1.0);
	fNormal = transpose(inverse(mat3(model)))*vNormal;
	fTex = vTex;

	for(int i = 0; i < dirLightsLen; i++){
		lightSpacePos = (dirLights[i].lightMatrix * vec4(fragPos, 1.0));
	}
}