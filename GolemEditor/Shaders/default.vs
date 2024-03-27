#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec4 Color;
layout (location = 4) in float TexIndex;
layout (location = 5) in float TilingFactor;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec4 Color;
out flat float TexIndex;
out float TilingIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	Color = Color;
	TexIndex = TexIndex;
	TilingFactor = TilingFactor;

    gl_Position = projection * view * model * vec4(Pos, 1.0);
	FragPos = vec3(model * vec4(Pos, 1.0));

	TexCoord = TexCoord;
    Normal = normalize(mat3(model) * Normal);
}
