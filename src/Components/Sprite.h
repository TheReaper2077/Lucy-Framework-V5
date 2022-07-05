#pragma once

#include <LucyGL/API.h>
#include <glm/glm.hpp>

namespace lucy::Components {
	struct Sprite {
		glm::vec4 color;
		glm::vec2 uv0;
		glm::vec2 uv1;
		lgl::Texture* texture = nullptr;
	};
}