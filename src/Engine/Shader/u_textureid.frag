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

uniform float u_textureid;

vec4 GetColor() {
	vec4 tex_color;

	switch (int(u_textureid)) {
		case 0:
			tex_color = texture(u_textures[0], uv0);
		case 1:
			tex_color = texture(u_textures[1], uv0);
		case 2:
			tex_color = texture(u_textures[2], uv0);
		case 3:
			tex_color = texture(u_textures[3], uv0);
		case 4:
			tex_color = texture(u_textures[4], uv0);
		case 5:
			tex_color = texture(u_textures[5], uv0);
		case 6:
			tex_color = texture(u_textures[6], uv0);
		case 7:
			tex_color = texture(u_textures[7], uv0);
		case 8:
			tex_color = texture(u_textures[8], uv0);
		case 9:
			tex_color = texture(u_textures[9], uv0);
		case 10:
			tex_color = texture(u_textures[10], uv0);
		case 11:
			tex_color = texture(u_textures[11], uv0);
		case 12:
			tex_color = texture(u_textures[12], uv0);
		case 13:
			tex_color = texture(u_textures[13], uv0);
		case 14:
			tex_color = texture(u_textures[14], uv0);
		case 15:
			tex_color = texture(u_textures[15], uv0);
		case 16:
			tex_color = texture(u_textures[16], uv0);
		case 17:
			tex_color = texture(u_textures[17], uv0);
		case 18:
			tex_color = texture(u_textures[18], uv0);
		case 19:
			tex_color = texture(u_textures[19], uv0);
		case 20:
			tex_color = texture(u_textures[20], uv0);
		case 21:
			tex_color = texture(u_textures[21], uv0);
		case 22:
			tex_color = texture(u_textures[22], uv0);
		case 23:
			tex_color = texture(u_textures[23], uv0);
		case 24:
			tex_color = texture(u_textures[24], uv0);
		case 25:
			tex_color = texture(u_textures[25], uv0);
		case 26:
			tex_color = texture(u_textures[26], uv0);
		case 27:
			tex_color = texture(u_textures[27], uv0);
		case 28:
			tex_color = texture(u_textures[28], uv0);
		case 29:
			tex_color = texture(u_textures[29], uv0);
		case 30:
			tex_color = texture(u_textures[30], uv0);
		case 31:
			tex_color = texture(u_textures[31], uv0);
	}

	return tex_color;
}

void main() {
	gl_FragColor = GetColor();
}