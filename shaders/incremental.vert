#version 440

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normalVec;
layout(location = 2) in vec2 texCoord;


struct DirectionalLight{
	vec3 intensity;
	vec3 direction;
	sampler2D shadowMap;
	mat4 lightMatrix;
};

const int dirLightsLen = 1;
uniform DirectionalLight dirLights[dirLightsLen];

out vec3 normal;
out vec3 fragPos;
out vec2 texC;
out vec4 lightSpacePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fragPos = (model * vec4(pos, 1.0)).xyz;
	gl_Position = projection*view*vec4(fragPos, 1.0);
	normal = transpose(inverse(mat3(model)))*normalVec;
	texC = texCoord;

	for(int i = 0; i < dirLightsLen; i++){
		lightSpacePos = (dirLights[i].lightMatrix * vec4(fragPos, 1.0));
	}
}