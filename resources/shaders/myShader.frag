#version 430 core
in vec3 FragPos;
in vec3 normals;

layout(location = 2) uniform vec3 camPos; //camera Position

out vec4 fragColor;
void main()
{
    //fragColor = vec4((1+normalize(normals))*0.5f, 1.0f);
    float l = (1+dot(normalize(vec3(10.0f, 10.0f, 10.0f)), normals))*0.5f;
    fragColor = vec4(l, l, l, 1.0f);
}