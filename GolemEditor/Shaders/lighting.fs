#version 330 core

out vec4 FragColor;
in vec2 UV;
in vec3 Normal;
in vec3 Position;

uniform sampler2D t0;
void main()
{
    vec3 t = texture(t0, UV).xyz;
    FragColor = vec4(t, 1) ;
}