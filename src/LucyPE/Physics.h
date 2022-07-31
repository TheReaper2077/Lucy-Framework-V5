#pragma once

#include <glm/glm.hpp>
#include <box2d/box2d.h>

namespace lpe {
	struct Physics {
		b2World world;

		void SetGravity(const glm::vec2& speed);
		void test();
	};
}