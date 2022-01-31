#version 440

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normalVec;
layout(location = 2) in vec2 texCoord;

out vec3 normal;
out vec3 fragPos;
out vec2 texC;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	fragPos = (model * vec4(pos, 1.0)).xyz;
	gl_Position = projection*view*vec4(fragPos, 1.0);
	normal = transpose(inverse(mat3(model)))*normalVec;
	texC = texCoord;
}