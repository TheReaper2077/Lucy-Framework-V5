#pragma once

#include <glm/glm.hpp>
#include <LucyGL/API.h>

namespace lucy {
	struct Camera {
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 position = { 0.0, 0.0, 0.0 };
		glm::vec3 world_front = { 0.0, 0.0, -1.0 };
		glm::vec3 front = world_front;
		glm::vec3 world_up = { 0.0f, 1.0f, 0.0f };
		glm::vec3 up = world_up;

		lgl::FrameBuffer* framebuffer = nullptr;

		bool enable = false;
		int width, height;
		int lastx, lasty;
		bool first_mouse = true;
		float fov = 45;
		float c_near = 0.001, c_far = 1000;
		float sensitivity = 0.1;

		Camera() {}
		Camera(bool enable): enable(enable) {}
	};
}