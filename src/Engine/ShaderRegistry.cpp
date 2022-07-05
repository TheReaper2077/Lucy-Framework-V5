#include "ShaderRegistry.h"
#include "Util.h"

#include <glad/glad.h>
#include <iostream>

#define ROOT "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\"

lucy::ShaderRegistry::ShaderRegistry() {
	shader_registry[TEXTUREID] = new lgl::Shader(ROOT"default.vert", ROOT"textureid.frag");
	shader_registry[U_TEXTUREID] = new lgl::Shader(ROOT"default.vert", ROOT"u_textureid.frag");
	shader_registry[COLOR] = new lgl::Shader(ROOT"default.vert", ROOT"color.frag");
	shader_registry[U_COLOR] = new lgl::Shader(ROOT"default.vert", ROOT"u_color.frag");
	shader_registry[TEXTUREARRAY] = new lgl::Shader(ROOT"default.vert", ROOT"texturearray.frag");

	int textures[32];
	for (int i = 0; i < 32; i++) {
		textures[i] = i;
	}

	shader_registry[TEXTUREID]->Bind();
	shader_registry[TEXTUREID]->SetUniformArray("u_textures", 32, textures);

	
	shader_registry[TEXTUREARRAY]->Bind();
	shader_registry[TEXTUREARRAY]->SetUniformi("texture", 0);
	
	shader_registry[U_TEXTUREID]->Bind();
	shader_registry[U_TEXTUREID]->SetUniformArray("u_textures", 32, textures);

	shader_registry[U_TEXTUREID]->UnBind();
}

lgl::Shader* lucy::ShaderRegistry::GetShader(ShaderFlag flags) {
	if (shader_registry.find(flags) == shader_registry.end()) {
		return nullptr;
	}

	return shader_registry[flags];
}
