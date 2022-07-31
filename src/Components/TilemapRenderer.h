#pragma once

#include <glm/glm.hpp>

namespace lucy {
	struct TilemapRenderer {
		bool disable_color = true;
		bool default_uv = false;

		glm::vec2 uv0 = { 0, 0 }, uv1 = { 1, 1 };

		
	};
}