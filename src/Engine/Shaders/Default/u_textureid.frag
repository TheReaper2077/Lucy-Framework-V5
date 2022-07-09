#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;
in float idx;
in vec2 uv;

layout(binding = 0) uniform sampler2D u_texture;

vec4 GetColor() {
	return texture(u_texture, uv);
}

void main() {
	gl_FragColor = mix(GetColor(), color, 0.5);
}