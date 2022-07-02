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

vec4 GetColor() {
	switch (int(textureid)) {
		case 0:
			return texture(u_textures[0], uv0);
		case 1:
			return texture(u_textures[1], uv0);
		case 2:
			return texture(u_textures[2], uv0);
		case 3:
			return texture(u_textures[3], uv0);
		case 4:
			return texture(u_textures[4], uv0);
		case 5:
			return texture(u_textures[5], uv0);
		case 6:
			return texture(u_textures[6], uv0);
		case 7:
			return texture(u_textures[7], uv0);
		case 8:
			return texture(u_textures[8], uv0);
		case 9:
			return texture(u_textures[9], uv0);
		case 10:
			return texture(u_textures[10], uv0);
		case 11:
			return texture(u_textures[11], uv0);
		case 12:
			return texture(u_textures[12], uv0);
		case 13:
			return texture(u_textures[13], uv0);
		case 14:
			return texture(u_textures[14], uv0);
		case 15:
			return texture(u_textures[15], uv0);
		case 16:
			return texture(u_textures[16], uv0);
		case 17:
			return texture(u_textures[17], uv0);
		case 18:
			return texture(u_textures[18], uv0);
		case 19:
			return texture(u_textures[19], uv0);
		case 20:
			return texture(u_textures[20], uv0);
		case 21:
			return texture(u_textures[21], uv0);
		case 22:
			return texture(u_textures[22], uv0);
		case 23:
			return texture(u_textures[23], uv0);
		case 24:
			return texture(u_textures[24], uv0);
		case 25:
			return texture(u_textures[25], uv0);
		case 26:
			return texture(u_textures[26], uv0);
		case 27:
			return texture(u_textures[27], uv0);
		case 28:
			return texture(u_textures[28], uv0);
		case 29:
			return texture(u_textures[29], uv0);
		case 30:
			return texture(u_textures[30], uv0);
		case 31:
			return texture(u_textures[31], uv0);
	}
}

void main() {
	gl_FragColor = GetColor();
}