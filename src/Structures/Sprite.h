#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>

namespace lucy {
	struct Sprite {
		glm::vec4 color = glm::vec4(0, 0, 0, 0);
		glm::vec2 uv0 = glm::vec2(0, 0);
		glm::vec2 uv1 = glm::vec2(1, 1);

		lgl::Texture* texture = nullptr;
	};
}