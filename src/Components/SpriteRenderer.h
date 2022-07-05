#pragma once

#include <LucyGL/API.h>
#include <glm/glm.hpp>

namespace lucy::Components {
	struct SpriteRenderer {
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
		glm::vec2 uv0 = glm::vec2(0, 0);
		glm::vec2 uv1 = glm::vec2(1, 1);
	};
}