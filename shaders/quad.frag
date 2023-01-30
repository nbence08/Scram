#version 440

in vec2 texCoord;

uniform sampler2D quad;

out vec4 color;

void main(){
	color = vec4(vec3(texture(quad, texCoord).r), 1.0);
}
