#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <LucyRE/LucyRE.h>

namespace lucy {
	enum LightType {
		DIRECTIONAL_LIGHT,
		AREAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,

		LightType_COUNT
	};

	struct Light {
		glm::vec3 color = { 1, 1, 1 };
		LightType mode = LightType::DIRECTIONAL_LIGHT;

		bool enable = true;

		float radius;
		float angle;
		float intensity;

		Light() {}
	};
}