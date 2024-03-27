#version 460 core

out vec4 FragColor;

struct PointLight
{
    vec3 position;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;
  
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    
    float constant;
    float linear;
    float quadratic; 
};

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 color2;

in vec4 Color;
in flat float TexIndex;
in float TilingFactor;

uniform sampler2D uTextures[32];

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform vec3 viewPos;

uniform int nbrDirLights;
uniform int nbrPointLights;
uniform int nbrSpotLights;

uniform DirLight dirLights[1];
uniform PointLight pointLights[10];
uniform SpotLight spotLights[10];

vec4 ProcessDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 ProcessPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 ProcessSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec4 texColor = Color;
    switch(int(TexIndex))
    {
        case 0: texColor *= texture(uTextures[0], TexCoord * TilingFactor); break;
        case 1: texColor *= texture(uTextures[1], TexCoord * TilingFactor); break;
        case 2: texColor *= texture(uTextures[2], TexCoord * TilingFactor); break;
        case 3: texColor *= texture(uTextures[3], TexCoord * TilingFactor); break;
        case 4: texColor *= texture(uTextures[4], TexCoord * TilingFactor); break;
        case 5: texColor *= texture(uTextures[5], TexCoord * TilingFactor); break;
        case 6: texColor *= texture(uTextures[6], TexCoord * TilingFactor); break;
        case 7: texColor *= texture(uTextures[7], TexCoord * TilingFactor); break;
        case 8: texColor *= texture(uTextures[8], TexCoord * TilingFactor); break;
        case 9: texColor *= texture(uTextures[9], TexCoord * TilingFactor); break;
        case 10: texColor *= texture(uTextures[10], TexCoord * TilingFactor); break;
        case 11: texColor *= texture(uTextures[11], TexCoord * TilingFactor); break;
        case 12: texColor *= texture(uTextures[12], TexCoord * TilingFactor); break;
        case 13: texColor *= texture(uTextures[13], TexCoord * TilingFactor); break;
        case 14: texColor *= texture(uTextures[14], TexCoord * TilingFactor); break;
        case 15: texColor *= texture(uTextures[15], TexCoord * TilingFactor); break;
        case 16: texColor *= texture(uTextures[16], TexCoord * TilingFactor); break;
        case 17: texColor *= texture(uTextures[17], TexCoord * TilingFactor); break;
        case 18: texColor *= texture(uTextures[18], TexCoord * TilingFactor); break;
        case 19: texColor *= texture(uTextures[19], TexCoord * TilingFactor); break;
        case 20: texColor *= texture(uTextures[20], TexCoord * TilingFactor); break;
        case 21: texColor *= texture(uTextures[21], TexCoord * TilingFactor); break;
        case 22: texColor *= texture(uTextures[22], TexCoord * TilingFactor); break;
        case 23: texColor *= texture(uTextures[23], TexCoord * TilingFactor); break;
        case 24: texColor *= texture(uTextures[24], TexCoord * TilingFactor); break;
        case 25: texColor *= texture(uTextures[25], TexCoord * TilingFactor); break;
        case 26: texColor *= texture(uTextures[26], TexCoord * TilingFactor); break;
        case 27: texColor *= texture(uTextures[27], TexCoord * TilingFactor); break;
        case 28: texColor *= texture(uTextures[28], TexCoord * TilingFactor); break;
        case 29: texColor *= texture(uTextures[29], TexCoord * TilingFactor); break;
        case 30: texColor *= texture(uTextures[30], TexCoord * TilingFactor); break;
        case 31: texColor *= texture(uTextures[31], TexCoord * TilingFactor); break;
    }

    color = texColor;

    color2 = 50;

    // Get view direction
    vec3 viewDir = normalize(viewPos - FragPos);

    vec4 light = vec4(0);

    for (int i = 0; i < nbrDirLights; i++)
        light += ProcessDirLight(dirLights[i], Normal, viewDir);

    for (int i = 0; i < nbrPointLights; i++)
        light += ProcessPointLight(pointLights[i], Normal, FragPos, viewDir);

    for (int i = 0; i < nbrSpotLights; i++)
        light += ProcessSpotLight(spotLights[i], Normal, FragPos, viewDir);
    
    FragColor = light * texture(ourTexture, TexCoord);
}

vec4 ProcessDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // Get light direction
    vec3 lightDir = normalize(-light.direction);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Combine
    return ambient + diffuse + specular;
}

vec4 ProcessPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Get light direction
    vec3 lightDir = normalize(light.position - fragPos);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Get the distance between the light and the pixel
    float distance = length(light.position - fragPos);

    // Compute light attenuation
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Combine
    return ambient + diffuse + specular;
}

vec4 ProcessSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Get light direction
    vec3 lightDir = normalize(light.position - fragPos);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    
    // Get the distance between the light and the pixel
    float dist = length(light.position - fragPos);
    
    // Compute light attenuation
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));    

    // Compute cutoff
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Apply attenuation
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    // Combine
    return ambient + diffuse + specular;
}
