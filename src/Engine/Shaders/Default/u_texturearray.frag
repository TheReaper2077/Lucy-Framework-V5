#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;
in float idx;
in vec2 uv;

layout(binding = 0) uniform sampler2DArray u_texturearray;

vec4 GetColor() {
	return texture(u_texturearray, vec3(uv, idx));
}

void main() {
	gl_FragColor = mix(GetColor(), color, 0.5);
}