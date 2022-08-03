#pragma once

#include <glm/glm.hpp>

namespace lucy {
	enum BodyType {
		STATIC,
		DYNAMIC,
		KINEMATIC,
	};

	struct Rigidbody2D {
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 force;

		BodyType type = STATIC;

		bool fixed_rotation = false;
		void* runtime_body = nullptr;

		float mass = 1;
	};
}