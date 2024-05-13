// #version 460 core
//
// in vec3 FragPos;
// in vec3 Normal;
// in vec2 TexCoord;
// out vec4 FragColor;
//
// struct PointLight
// {
//     vec3 position;
//     
//     vec4 ambient;
//     vec4 diffuse;
//     vec4 specular;
//
//     float constant;
//     float linear;
//     float quadratic;
// };
//
// struct DirLight
// {
//     vec3 direction;
//     
//     vec4 ambient;
//     vec4 diffuse;
//     vec4 specular;
// };
//
// struct SpotLight
// {
//     vec3 position;
//     vec3 direction;
//
//     float cutOff;
//     float outerCutOff;
//   
//     vec4 ambient;
//     vec4 diffuse;
//     vec4 specular;
//     
//     float constant;
//     float linear;
//     float quadratic; 
// };