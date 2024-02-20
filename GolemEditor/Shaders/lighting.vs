#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
    mat4 PVM = P * V * M; 
    UV = aUV;
    Normal = aNormal;
    Position = aPos;
    gl_Position = PVM*vec4(aPos, 1.0);
}