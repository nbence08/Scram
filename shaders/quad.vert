#version 440

layout(location = 0) in vec3 vPos;

out vec2 texCoord;

void main(){
	gl_Position = vec4(vPos, 1.0f);
	texCoord = (vPos.xy + vec2(1)) * (1.0f/2.0f);
}