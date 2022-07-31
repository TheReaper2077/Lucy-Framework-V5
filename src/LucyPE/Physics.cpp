#include "Physics.h"

void lpe::Physics::SetGravity(const glm::vec2& speed) {
	world.SetGravity({ speed.x, speed.y });
}

void lpe::Physics::test() {
	
}

