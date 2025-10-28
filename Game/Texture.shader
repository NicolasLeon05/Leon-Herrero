#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
	color = aColor;
    texCoord = aTexCoord;
};

#shader fragment
#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D Texture;

void main()
{
	fragColor = texture(Texture, texCoord) * color;
};