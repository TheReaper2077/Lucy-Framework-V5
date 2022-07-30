#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <Engine/Window.h>

namespace lucy {
	enum ViewMode {
		ViewMode_None,
		ViewMode_FPS,
		ViewMode_Editor,

		ViewMode_COUNT
	};

	struct Camera {
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 position = { 0.0, 0.0, 0.0 };
		glm::vec3 world_front = { 0.0, 0.0, -1.0 };
		glm::vec3 front = world_front;
		glm::vec3 world_up = { 0.0, 1.0, 0.0 };
		glm::vec3 up = world_up;

		glm::vec4 clear_color = { 0, 0, 0, 0 };

		bool enable = false;
		int width, height;
		int lastx, lasty;
		bool first_mouse = true;
		float fov = 45;
		float c_near = 0.01, c_far = 1000;
		float sensitivity = 0.1;

		bool is_maincamera = true;

		ViewMode mode = ViewMode_None;

		Camera() {}
		Camera(ViewMode mode): mode(mode) {}
		Camera(ViewMode mode, bool enable): mode(mode), enable(enable) {}
		Camera(ViewMode mode, bool enable, bool is_maincamera): mode(mode), enable(enable), is_maincamera(is_maincamera) {}
	};
}