#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 dir;

void main() {
gl_Position = vec4(aPos, 1.0f);
mat4 viewTmp = mat4(mat3(view));
mat4 inversedViewProjection = inverse(projection * viewTmp);
vec4 dir4 = inversedViewProjection * vec4(aPos, 1.0);
dir = vec3(dir4);
}