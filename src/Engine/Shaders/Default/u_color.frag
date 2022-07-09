#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;
in vec2 uv;

uniform vec4 u_color;

vec4 GetColor() {
	return u_color;
}

void main() {
	gl_FragColor = GetColor();
}