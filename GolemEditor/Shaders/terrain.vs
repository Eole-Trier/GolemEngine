#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float minHeight;
uniform float maxHeight;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out float minY; // Varying output for min height
out float maxY; // Varying output for max height


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    
    TexCoord = aTexCoord;
    minY = minHeight; // Set the varying min height value
    maxY = maxHeight; // Set the varying max height value
}