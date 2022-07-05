#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;

in vec2 uv0;
in vec2 uv1;
in vec2 uv2;
in vec2 uv3;
in vec2 uv4;
in vec2 uv5;
in vec2 uv6;
in vec2 uv7;

uniform sampler2D u_textures[32];

uniform vec4 u_color;

vec4 GetColor() {
	return u_color;
}

void main() {
	gl_FragColor = GetColor();
}