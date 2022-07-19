#pragma once

#include <glm/glm.hpp>

namespace lucy {
	enum LightMode {
		DIRECTIONAL_LIGHT,
		AREAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,

		LightType_COUNT
	};

	struct Light {
		glm::vec3 color = { 1, 1, 1 };
		LightMode mode = LightMode::DIRECTIONAL_LIGHT;

		bool enable = true;

		Light() {}
		Light(const glm::vec3& color): color(color) {}
		Light(const glm::vec3& color, LightMode mode): color(color), mode(mode) {}
		Light(LightMode mode): mode(mode) {}
	};
}