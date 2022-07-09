#pragma once

#include <LucyGL/API.h>
#include <string>
#include <unordered_map>

namespace lucy {
	enum ShaderFlag {
		TEXTURE = 1 << 0,
		TEXTUREARRAY = 1 << 1,

		MIX = 1 << 2,
		COLOR = 1 << 3,
		PBR = 1 << 4,
		UNIFORM = 1 << 5,
	};

	class ShaderRegistry {
		std::unordered_map<size_t, lgl::Shader*> shader_registry;

	public:
		ShaderRegistry();
		lgl::Shader* GetShader(const size_t flags);
		lgl::Shader* Generate(const size_t flags);
	};
}