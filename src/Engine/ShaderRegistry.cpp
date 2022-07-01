#include "ShaderRegistry.h"
#include "Util.h"

#define ROOT "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shader\\"

lucy::ShaderRegistry::ShaderRegistry() {
	shader_registry[TEXTUREID] = new lgl::Shader(ROOT"default.vert", ROOT"textureid.frag");
	shader_registry[U_TEXTUREID] = new lgl::Shader(ROOT"default.vert", ROOT"u_textureid.frag");
	shader_registry[COLOR] = new lgl::Shader(ROOT"default.vert", ROOT"color.frag");
	shader_registry[U_COLOR] = new lgl::Shader(ROOT"default.vert", ROOT"u_color.frag");

	uint32_t u_textures[32];
	for (int i = 0; i < 32; i++) {
		u_textures[i] = i;
	}
	shader_registry[TEXTUREID]->Bind();
	shader_registry[TEXTUREID]->SetUniformArray("u_textures", 32, u_textures);
}

lgl::Shader* lucy::ShaderRegistry::GetShader(ShaderFlag flags) {
	if (shader_registry.find(flags) == shader_registry.end()) {
		return nullptr;
	}

	return shader_registry[flags];
}
