#version 460 core

in vec3 FragPos; // Input position from vertex shader
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor; // Output color of the fragment

uniform float maxHeight; // Maximum height of the heightmap

void main()
{
    // Normalize the height to range [0, 1]
    float normalizedHeight = FragPos.y / maxHeight;

    // Set color based on normalized height
    FragColor = vec4(normalizedHeight, normalizedHeight, normalizedHeight, 1.0);
}