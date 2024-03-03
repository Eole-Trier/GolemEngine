/*#version 460 core

out vec4 outColor;
  
in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D ourTexture;

void main()
{
    vec3 t = texture(ourTexture, texCoords).xyz;
    outColor = vec4(t, 1);
}*/

#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture1, TexCoord);
}