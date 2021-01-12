#version 430 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normals;

uniform mat4 mvp; // model view projection
uniform mat4 model; // model to world

out vec3 fragPos;
out vec3 normals;

void main() {
    fragPos = vec3(model * vec4(in_vertex , 1.0f));
    gl_Position = mvp * vec4(in_vertex , 1.0f);

    normals = vec3(transpose(inverse(model))) * in_normals;
}