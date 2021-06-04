#version 330
precision highp float;

uniform sampler2DMS tex;

uniform int samples;
uniform float recSamples;

in vec2 uv;

uniform float recGamma;
uniform vec2 size;

void main(){
	vec4 gammaVec = vec4(recGamma, recGamma, recGamma, 1.0);

	int u = int(uv.x*float(size.x));
	int v = int(uv.y*float(size.y));
	ivec2 iuv = ivec2(u, v);

	vec4 color = vec4(0.0);
	for(int i = 0; i < samples; i++){
		vec4 texel = texelFetch(tex, iuv, i);
		color += pow(texel, gammaVec);
	}
	gl_FragColor = recSamples*color;
}