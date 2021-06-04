#version 330
precision highp float;

out vec4 fragColor;

in vec3 normal;

void main(){
	fragColor = vec4(abs(normal), 1.0);
}