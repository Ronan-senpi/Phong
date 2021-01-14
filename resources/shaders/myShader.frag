#version 430 core
in vec3 FragPos;
in vec3 normals;

layout(location = 2) uniform vec3 camPos; //camera Position
layout(location = 3) uniform vec3 objectColor;
layout(location = 4) uniform vec3 lightColor;
layout(location = 5) uniform vec3 lightPos;

out vec4 fragColor;
void main()
{
//     ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(normals);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}