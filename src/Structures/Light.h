#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>

namespace lucy {
	enum LightMode {
		DIRECTIONAL_LIGHT,
		AREAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,

		LightType_COUNT
	};

	struct Light: public ComponentTemplate {
		glm::vec3 color = { 1, 1, 1 };
		LightMode mode = LightMode::DIRECTIONAL_LIGHT;

		bool enable = true;

		Light() {}

		/// @brief Bind Shader Before Use
		/// @param shader 
		/// @param idx 
		void Bind(lgl::Shader* shader, int idx);

		void ImGuiRender() override;
	};
}