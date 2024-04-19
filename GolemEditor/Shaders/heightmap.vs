#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float maxHeight;

out vec3 o_newPosition;
out vec2 o_texCoord;
out float o_maxHeight;


void main()
{
    vec3 newPosition = vec3(position.x, position.y, position.z);
    gl_Position = projection * view * model * vec4(newPosition, 1.0f);

    o_newPosition = newPosition;
    o_texCoord = texCoord;
    o_maxHeight = maxHeight;
    
}