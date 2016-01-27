#version 330 core 
layout(location = 0 ) in vec3 vertexPosition_modelSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2 ) in vec3 vertexNormal_modelSpace;

//out vec3 ourColor; 
out vec2 UV;
out vec3 position_worldSpace;
out vec3 normal_cameraSpace;
out vec3 eyeDirection_cameraSpace;
out vec3 lightDirection_cameraSpace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPosition_worldSpace;
void main() 
{ 

	gl_Position = MVP*M*vec4(vertexPosition_modelSpace,1);
	
	position_worldSpace = (M*vec4(vertexPosition_modelSpace,1)).xyz;

	vec3 vertexPosition_cameraSpace = (V*M*vec4(vertexPosition_modelSpace,1)).xyz;

	eyeDirection_cameraSpace = vec3(0,0,0) - vertexPosition_cameraSpace;

	vec3 lightPosition_cameraSpace = (V* vec4(lightPosition_worldSpace,1)).xyz;
	lightDirection_cameraSpace = lightPosition_cameraSpace + eyeDirection_cameraSpace;

	normal_cameraSpace = (V*M* vec4(vertexNormal_modelSpace,0)).xyz;
	
	UV = vec2(vertexUV.x,vertexUV.y);
}