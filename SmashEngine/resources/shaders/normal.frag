#version 330 core
in vec2 UV;
in vec3 position_worldSpace;
in vec3 normal_cameraSpace;
in vec3 eyeDirection_cameraSpace;
in vec3 lightDirection_cameraSpace;

out vec4 color; 

uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 lightPosition_worldSpace;

void main() 
{ 
	vec3 lightColor = vec3(1,1,1);
	float lightPower = 500.0f;

	float distance = length(lightPosition_worldSpace - position_worldSpace);

	vec3 materialDiffuseColor = texture2D(myTextureSampler,UV).rgb;
	vec3 materialAmbientColor = vec3(0.1,0.1,0.1)*materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.3,0.3,0.3);
	vec3 n = normalize(normal_cameraSpace);
	vec3 l = normalize(lightDirection_cameraSpace);

	vec3 e = normalize(eyeDirection_cameraSpace);
	vec3 r = reflect(-l,n);

	float cosAlpha = clamp(dot(e,r),0,1);

	float cosTheta = clamp(dot(n,l),0.0f,1.0f);
	color.a = 0.3;
	//color.rgb = materialAmbientColor +
	//		materialDiffuseColor*lightColor*lightPower*cosTheta/(distance*distance)+
	//		materialSpecularColor*lightColor*lightPower*pow(cosAlpha,5)/(distance*distance);
	color.rgb = materialAmbientColor +
			materialDiffuseColor+
			materialSpecularColor;
}