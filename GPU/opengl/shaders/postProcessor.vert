#version 330
precision highp float;

layout (location = 0) in vec3 aPos;

out vec2 uv;

void main(){
	gl_Position = vec4(aPos, 1.0);

	uv=aPos.xy;

	uv = 0.5* (aPos.xy+1.0);
}
