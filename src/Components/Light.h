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
		glm::vec4 color;
		LightMode mode;

		bool enable = true;
	};
}