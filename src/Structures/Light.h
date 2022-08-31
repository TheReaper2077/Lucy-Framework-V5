#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <LucyRE/LucyRE.h>

namespace lucy {
	enum LightType {
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		AREAL_LIGHT,
		SPOT_LIGHT,

		LightType_COUNT
	};

	struct Light {
		glm::vec4 color = { 1, 1, 1, 1 };
		LightType mode = LightType::DIRECTIONAL_LIGHT;

		bool enable = true;

		float radius;
		float angle;
		float intensity;

		float ambient = 0.5;
		float diffuse = 0.2;
		float specular = 1;

		Light() {}
		~Light() {}
	};
}