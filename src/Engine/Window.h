#pragma once

#include <glm/vec2.hpp>

namespace lucy {
	struct Window {
		glm::vec2 pos = { 50, 50 };
		glm::vec2 size = { 1280, 640 };

		std::string title = "Lucy Framework V4";
	};
}