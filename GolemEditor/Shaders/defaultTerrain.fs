#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in float minY; // Input from vertex shader
in float maxY; // Input from vertex shader

void main()
{
    float normalizedHeight = 0.0f;

    if (maxY > 0.0f)
    {
        normalizedHeight = FragPos.y / maxY; // Normalize the y-coordinate of the fragment position for positive maxY
    }
    else if (minY < 0.0f)
    {
        normalizedHeight = (FragPos.y / minY); // Normalize the y-coordinate of the fragment position for negative maxY. To have the white shown at the highest point and not
                                               // the lowest, add "1 -" before "(FragPos.y / minY);" 
    }

    FragColor = vec4(normalizedHeight, normalizedHeight, normalizedHeight, 1.0); // Set the fragment color based on the normalized height
}