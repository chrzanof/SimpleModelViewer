#version 330 core

out vec4 fragColor;
in vec3 dir; 
uniform samplerCube env;

void main() {
	fragColor = texture(env, dir);
}