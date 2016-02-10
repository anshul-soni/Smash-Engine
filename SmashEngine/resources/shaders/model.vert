#version 330 core 
layout(location = 0 ) in vec3 vertexPosition_modelSpace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
void main() 
{ 
	gl_Position = MVP*M*vec4(vertexPosition_modelSpace,1);
	
	UV = vec2(vertexUV.x,vertexUV.y);
}