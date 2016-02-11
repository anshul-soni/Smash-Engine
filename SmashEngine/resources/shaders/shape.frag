#version 330 core
uniform vec4 fragmentColor;

out vec4 color;

void main()
{
	color.a =1.0;
	color = fragmentColor;
}