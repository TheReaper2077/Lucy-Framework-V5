#include "ShaderRegistry.h"
#include "Util.h"
#include <assert.h>

#include <glad/glad.h>
#include <iostream>

#define ROOT "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\"

#define FS_INIT \
"#version 450 core\n" \
"\n" \
"in vec3 normal;\n" \
"in vec4 color;\n" \
"in float textureid;\n" \
"in float idx;\n" \
"in vec2 uv;\n" \

#define FS_Func(type, name, code) std::string(type) + " " + std::string(name) + std::string(" {\n") + code + std::string("}\n")
#define FS_GetTexFunc(code) FS_Func("vec4", "GetTexture()", code)
#define FS_GetColFunc(code) FS_Func("vec4", "GetColor()", code)
#define FS_MainFunc(code) FS_Func("void", "main()", code)

lucy::ShaderRegistry::ShaderRegistry() {
	Generate(TEXTURE);
	Generate(UNIFORM | TEXTURE);
	Generate(COLOR);
	Generate(UNIFORM | COLOR);
}

lgl::Shader* lucy::ShaderRegistry::GetShader(const size_t flags) {
	if (shader_registry.find(flags) == shader_registry.end()) {
		return Generate(flags);
	}

	return shader_registry[flags];
}

lgl::Shader* lucy::ShaderRegistry::Generate(const size_t flags) {
	std::string vertex_shader = util::ReadFile("D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\default.vert");
	std::string fragement_shader = FS_INIT;

	assert(!(flags & TEXTURE) || !(flags & TEXTUREARRAY));

	if (flags & TEXTURE) {
		std::string code;
		std::string texture;

		if (flags & UNIFORM) {
			fragement_shader += "\nuniform int u_textureid;\n";
			code += "	switch(u_textureid) {\n";
		}
		else {
			code += "	switch(int(textureid)) {\n";
		}

		for (int i = 0; i < 32; i++) {
			code += "		case " + std::to_string(i) + ":\n";
			code += "			return texture(u_textures[" + std::to_string(i) + "], uv);\n";
		}

		code += "	}\n";

		fragement_shader += "\nuniform sampler2D u_textures[32];\n";
		fragement_shader += FS_GetTexFunc(code);
	}
	
	if (flags & TEXTUREARRAY) {
		fragement_shader += "\nuniform sampler2D u_texturearray;\n";
		fragement_shader += FS_GetTexFunc("	return texture(u_texturearray, vec3(uv, idx));\n");
	}

	// if (flags & U_COLOR) {
	// 	fragement_shader += "uniform vec4 u_color;\n";
	// 	fragement_shader += FS_GetColFunc("	return u_color;\n");
	// }
	// if (flags & COLOR) {
	// 	fragement_shader += FS_GetColFunc("	return color;\n");
	// }

	{
		std::string code;

		if ((flags & TEXTURE || flags & TEXTUREARRAY) && (flags & COLOR)) {
			code += "	gl_FragColor = mix(GetTexture(), color, 0.5);\n";
		} else if (flags & TEXTURE || flags & TEXTUREARRAY) {
			code += "	gl_FragColor = GetTexture();\n";
		} else {
			code += "	gl_FragColor = color;\n";
		}

		fragement_shader += FS_MainFunc(code);
	}

	std::cout << fragement_shader;

	shader_registry[flags] = new lgl::Shader(vertex_shader, fragement_shader, false);
	auto* shader = shader_registry[flags];

	if (flags & TEXTURE) {
		int textures[32];
		for (int i = 0; i < 32; i++) {
			textures[i] = i;
		}

		shader->Bind();
		shader->SetUniformArray("u_textures", 32, textures);
		shader->UnBind();
	}

	if (flags & TEXTUREARRAY) {
		shader->Bind();
		shader->SetUniformi("u_texturearray", 0);
		shader->UnBind();
	}

	return shader;
}
