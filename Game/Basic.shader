#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	color = aColor;
};

#shader fragment
#version 330 core

out vec4 fragColor;

in vec4 color;

void main()
{
	fragColor = color;
};