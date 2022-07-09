#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;
in float idx;

in vec2 uv;

vec4 GetColor() {
	return color;
}

void main() {
	gl_FragColor = GetColor();
}