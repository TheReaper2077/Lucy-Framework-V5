#pragma once

#include <glm/glm.hpp>
#include <LucyGL/API.h>

namespace lucy::Components {
	struct Camera {
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 world_front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 front = world_front;
		glm::vec3 right;
		glm::vec3 world_right;
		glm::vec3 up;

		bool is_editorcamera;

		void Update();
		void UpdateEditor();
	};
}