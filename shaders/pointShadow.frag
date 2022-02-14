#version 440

in vec4 fragPos;

struct PointLight{
	vec3 intensity;
	vec3 attenuation;
	vec3 position;
	mat4 lightMatrices[6];
	float farPlane;
};

const int pointLightsLen = 1;
uniform PointLight pointLights[pointLightsLen];
uniform int lightIndex;

void main(){
	gl_FragDepth = length(fragPos.xyz - pointLights[lightIndex].position)/pointLights[lightIndex].farPlane;
}