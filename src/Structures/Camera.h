#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <Lucy/Window.h>
#include "Transform.h"
#include <Lucy/ECS.h>

namespace lucy {
	struct Camera;

	typedef void(*CAMERA_UPDATE_FUNC)(Entity entity, Transform& transform, Camera& camera);

	struct Camera {
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 position = { 0.0, 0.0, 0.0 };
		glm::vec3 offset = { 0.0, 0.0, 0.0 };
		glm::vec3 world_front = { 0.0, 0.0, -1.0 };
		glm::vec3 front = world_front;
		glm::vec3 world_up = { 0.0, 1.0, 0.0 };
		glm::vec3 up = world_up;

		glm::vec4 clear_color = { 0, 0, 0, 0 };
		uint32_t clear_flags = lgl::COLOR_BUFFER_BIT | lgl::DEPTH_BUFFER_BIT;

		int width, height;
		int lastx, lasty;
		bool first_mouse = true;
		float fov = 45;
		float c_near = 0.01, c_far = 1000;
		float sensitivity = 0.5;

		bool enable = true;

		lgl::FrameBuffer* framebuffer = nullptr;
		std::string skybox_id;

		CAMERA_UPDATE_FUNC update = nullptr;

		Camera() {}
		~Camera();
	};
}