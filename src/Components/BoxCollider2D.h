#pragma once

#include <glm/glm.hpp>

namespace lucy {
	struct BoxCollider2D {
		glm::vec2 offset = { 0, 0 };
		glm::vec2 size = { 25, 25 };

		bool use_scale = true;

		float density = 1.0;
		float friction = 0.5;
		float restitution = 0.0;
		float restitution_threshold = 0.5;
	};
}