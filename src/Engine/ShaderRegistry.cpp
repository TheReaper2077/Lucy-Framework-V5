#include "ShaderRegistry.h"
#include "Util.h"

#define ROOT "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shader\\"

lucy::ShaderRegistry::ShaderRegistry() {
	shader_registry[TEXTUREID] = lgl::Shader(ROOT"default.vert", ROOT"texture.frag");
	shader_registry[U_TEXTUREID] = lgl::Shader(ROOT"default.vert", ROOT"u_texture.frag");
	shader_registry[COLOR] = lgl::Shader(ROOT"default.vert", ROOT"color.frag");
	shader_registry[U_COLOR] = lgl::Shader(ROOT"default.vert", ROOT"u_color.frag");
}

lgl::Shader* lucy::ShaderRegistry::GetShader(ShaderFlag flags) {
	if (shader_registry.find(flags) == shader_registry.end()) {
		return nullptr;
	}

	return &shader_registry[flags];
}
