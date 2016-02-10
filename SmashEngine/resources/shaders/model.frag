#version 330 core
in vec2 UV;

out vec4 color; 

uniform sampler2D myTextureSampler;
uniform mat4 MV;

void main() 
{ 

	//vec4 top         = texture(myTextureSampler, vec2(UV.x, UV.y + 1.0 / 200.0));
	//vec4 bottom      = texture(myTextureSampler, vec2(UV.x, UV.y - 1.0 / 200.0));
	//vec4 left        = texture(myTextureSampler, vec2(UV.x - 1.0 / 300.0, UV.y));
	//vec4 right       = texture(myTextureSampler, vec2(UV.x + 1.0 / 300.0, UV.y));
	//vec4 topLeft     = texture(myTextureSampler, vec2(UV.x - 1.0 / 300.0, UV.y + 1.0 / 200.0));
	//vec4 topRight    = texture(myTextureSampler, vec2(UV.x + 1.0 / 300.0, UV.y + 1.0 / 200.0));
	//vec4 bottomLeft  = texture(myTextureSampler, vec2(UV.x - 1.0 / 300.0, UV.y - 1.0 / 200.0));
	//vec4 bottomRight = texture(myTextureSampler, vec2(UV.x + 1.0 / 300.0, UV.y - 1.0 / 200.0));
	//vec4 sx = -topLeft - 2 * left - bottomLeft + topRight   + 2 * right  + bottomRight;
	//vec4 sy = -topLeft - 2 * top  - topRight   + bottomLeft + 2 * bottom + bottomRight;
	//vec4 sobel = sqrt(sx * sx + sy * sy);
	//color = sobel;
	vec3 materialDiffuseColor = texture2D(myTextureSampler,UV).rgb;
	vec3 materialAmbientColor = vec3(0.1,0.1,0.1)*materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.3,0.3,0.3);
	color.a = 0.3;
	color.rgb = materialAmbientColor +
			materialDiffuseColor+
			materialSpecularColor;
}