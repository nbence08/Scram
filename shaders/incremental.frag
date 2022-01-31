#version 440

precision highp float;

const float PI = 3.141592653589793238;

struct DirectionalLight{
	vec3 intensity;
	vec3 direction;
};

struct PointLight{
	vec3 intensity;
	vec3 attenuation;
	vec3 position;
	//effective range of light should be added to be able to optimize point lights calculations
	//by being able to remove light calculations based completely on distance from fragPos
};

struct SpotLight{
	vec3 intensity;
	vec3 attenuation;
	vec3 position;
	vec3 direction;

	float dimAngle;
	float angle;
};

struct Material{
	vec3 albedoVec;
	sampler2D albedoTexture;
	float smoothness;
	float metalness;
	bool albedo_is_texture;
	bool has_emission;
	sampler2D emissionTexture;
};

out vec4 color;

in vec3 normal;
in vec3 fragPos;
in vec2 texC;


uniform vec3 cameraPos;

const int pointLightsLen = 1;
uniform PointLight pointLights[pointLightsLen];
const int dirLightsLen = 1;
uniform DirectionalLight dirLights[dirLightsLen];
const int spotLightsLen = 1;
uniform SpotLight spotLights[spotLightsLen];

//default material by definition is 0
uniform Material materials[1];

//Beckmann distribution
float Beckmann(in vec3 L, in vec3 V, in vec3 N, in vec3 H ){

	float alpha = acos(dot(N, H));
	float cosAlphaSq = pow(cos(alpha), 2);

	float roughness = 1.001f - materials[0].smoothness;
	float mSq = pow(roughness, 2);

	return ( exp( - (1.0 - cosAlphaSq)/(cosAlphaSq*mSq) )/(PI*mSq*pow(cosAlphaSq, 2)) );
}

//Schlick approximation of Fresnel coefficient
vec3 Schlick(in vec3 H, in vec3 V, in vec3 F0){
	float cosTheta = dot(H, V);
	return F0 + (1.0-F0)*pow(1.0-cosTheta, 5.0);
}

//Geometric Attenuation factor
float GeomAtten(in vec3 H, in vec3 N, in vec3 V, in vec3 L, out float VN, out float NL){
	VN = dot(V, N);
	NL = dot(N, L);
	float coeff = 2.0*dot(H,N)/dot(V,H);
	float A = coeff * VN;
	float B = coeff * NL;
	return min(1.0, min(A, B));
}

vec3 cookTorranceCalculation(in vec3 texColor, in vec3 L, in vec3 V, in vec3 H, in vec3 F0, in vec3 intensity){
		float VN, NL;
		vec3 N = normalize(normal);

		float D = Beckmann(L, V, N, H);
		vec3 F = Schlick(H, V, F0);
		float G = GeomAtten(H, N, V, L, VN, NL);

		vec3 fCookTorrance = D*F*G/(4*VN*NL);
		vec3 fLambert = texColor.xyz / PI;// clamp(dot(normalize(normal), normalize(light.position - fragPos)),0.0f, 1.0f );

		vec3 ks = F0;
		vec3 kd = vec3(1.0) - ks;
		NL = clamp(NL, 0.0, 1.0);

		return clamp((fCookTorrance * ks + fLambert * kd) * (intensity) * NL, 0, 1000000);
}

//Cook-Torrance Point Lights
vec3 ctPointLights(in vec4 texColor){
	vec3 accu = vec3(0.0, 0.0, 0.0);
	
	for(int i = 0; i < pointLightsLen; i++){
		PointLight light = pointLights[i];

		vec3 L, V, H, F0;
		L = normalize(light.position - fragPos);
		V = normalize(cameraPos - fragPos);
		H = normalize(L+V);
		F0 = mix(vec3(0.04), texColor.xyz, materials[0].metalness);

		float d = length(fragPos - light.position);
	
		float attenuationCoeff = 1.0/ (light.attenuation.x + light.attenuation.y*d + light.attenuation.z*d*d);

		
		accu += cookTorranceCalculation(texColor.xyz, L, V, H,  F0, light.intensity) * attenuationCoeff;
	}
	return  accu;
}

vec3 ctDirLights(in vec4 texColor){
	vec3 accu = vec3(0.0, 0.0, 0.0);
	
	for(int i = 0; i < dirLightsLen; i++){
		DirectionalLight light = dirLights[i];

		vec3 L, V, H, F0;
		L = normalize(light.direction);
		V = normalize(cameraPos - fragPos);
		H = normalize(L+V);
		F0 = mix(vec3(0.04), texColor.xyz, materials[0].metalness);

		accu += cookTorranceCalculation(texColor.xyz, L, V, H,  F0, light.intensity);
	}
	return  accu;
}

vec3 ctSpotLights(in vec4 texColor){
	vec3 accu = vec3(0.0, 0.0, 0.0);
	
	for(int i = 0; i < spotLightsLen; i++){
		SpotLight light = spotLights[i];

		vec3 L, V, H, F0;
		L = normalize(light.direction);
		V = normalize(cameraPos - fragPos);
		H = normalize(L+V);
		F0 = mix(vec3(0.04), texColor.xyz, materials[0].metalness);

		vec3 light2frag = (fragPos - light.position);

		float d = length(light2frag);
		light2frag = normalize(light2frag);

		float similarness = dot(light2frag, L);

		float dim = 1.0;

		if(light.angle > similarness) return vec3(0.0, 0.0, 0.0);
		if(light.dimAngle > similarness)
			dim = (similarness - light.angle)/(light.dimAngle - similarness);
	
		float attenuationCoeff = 1.0/ (light.attenuation.x + light.attenuation.y*d + light.attenuation.z*d*d);

		accu += cookTorranceCalculation(texColor.xyz, L, V, H,  F0, light.intensity) * dim * attenuationCoeff;
	}
	return  accu;
}

vec3 drawScene(in vec4 texColor){
	vec3 accu = vec3(0.0f, 0.0f, 0.0f);
	accu += ctPointLights(texColor);
	accu += ctDirLights(texColor);
	//accu += ctSpotLights(texColor);
	
	return accu;
}

void main(){
	
		
	vec4 texColor;
	if(materials[0].albedo_is_texture){
		texColor = vec4(texture(materials[0].albedoTexture, texC));
	}
	else {
		texColor = vec4(materials[0].albedoVec, 1.0);
	}

	vec3 emission = vec3(0);
	if(materials[0].has_emission){
		emission = texture(materials[0].emissionTexture, texC).xyz;
	}

	float tcLength = length(texColor.xyz);
	/*if(tcLength > 1.0){
		texColor = vec4(normalize(texColor.xyz), 1.0); 
	}*/
	
	color = vec4(pow(drawScene(texColor) + 0.1*texColor.xyz + emission, vec3(1/2.2)), 1.0);	
}