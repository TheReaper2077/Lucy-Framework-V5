#pragma once

#include <LucyGL/API.h>
#include <string>
#include <unordered_map>

namespace lucy {
	enum ShaderFlag {
		TEXTUREID = 1,
		U_TEXTUREID,
		COLOR,
		U_COLOR,
		PBR_TEXTUREID,
		PBR_U_TEXTUREID,
		PBR_COLOR,
		PBR_U_COLOR,

		ShaderFlag_COUNT
	};

	class ShaderRegistry {
		std::unordered_map<ShaderFlag, lgl::Shader> shader_registry;

	public:
		ShaderRegistry();
		lgl::Shader* GetShader(ShaderFlag flags);
	};
}