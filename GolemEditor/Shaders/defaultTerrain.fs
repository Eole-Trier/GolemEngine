#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in float maxY; // Input from vertex shader

void main()
{
    float normalizedHeight = 0.0f;

    if (maxY == 0.0f)
    {
        normalizedHeight = 1.0f;
    }
    else if (maxY != 0.0f)
    {
        normalizedHeight = FragPos.y / maxY; // Normalize the y-coordinate of the fragment position for positive maxY
    }

    FragColor = vec4(normalizedHeight, normalizedHeight, normalizedHeight, 1.0); // Set the fragment color based on the normalized height
}