#version 450 core

in vec2 uv;

uniform sampler2D u_texture;

void main() {
	// gl_FragData[0] = texture(u_texture, uv);
	gl_FragData[0] = vec4(1);
}