#version 330 core 
layout(location = 0 ) in vec3 vertexPosition_modelSpace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
void main() 
{ 
	gl_Position = MVP*M*vec4(vertexPosition_modelSpace,1);
}