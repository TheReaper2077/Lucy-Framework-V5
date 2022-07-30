#define FUNC_TEXTUREARRAY

uniform sampler2DArray u_texturearray;

vec4 GetTexture(const int id, const vec3 uv) {
	return texture(u_texturearray, uv);
}