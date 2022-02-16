#version 440

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

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

out vec4 fragPos;

void main(){
	for(int i = 0; i < 6; i++){
		gl_Layer = i;
		for(int j = 0; j < 3; j++){
			fragPos = gl_in[j].gl_Position;
			gl_Position = pointLights[lightIndex].lightMatrices[i] * gl_in[j].gl_Position;
			EmitVertex();
		}
		EndPrimitive();
	}
}