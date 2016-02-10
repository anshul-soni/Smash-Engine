#version 330 core 
layout(location = 0 ) in vec3 vertexPosition_modelSpace;
layout(location = 1) in vec3 vertexColor;

out vec4 fragmentColor;

uniform mat4 MVP;
uniform mat4 M;
void main() 
{ 
	gl_Position = MVP*M*vec4(vertexPosition_modelSpace,1);
	fragmentColor = vertexColor;
}