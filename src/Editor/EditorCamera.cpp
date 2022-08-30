#include <Lucy/Lucy.h>
#include "EditorCamera.h"
#include "EditorState.h"
#include <iostream>

static auto& registry = lucy::Registry::Instance();
static bool toggle = false;
static float scrollspeed = .75;

static float last_height, last_width;

// struct Info {
// 	bool toggle = false;
// 	float scrollspeed = 0.75;
// };

// std::unordered_map<lucy::Entity, Info> camera_info_map;

void lucy::EditorCameraUpdate(Entity entity, Transform& transform, Camera& camera) {
	auto& state = registry.store<lucy::EditorState>();

	auto norm_cursor_pos = Events::GetCursorPosNormalized(0, 0, camera.width, camera.height);
	auto cursor_pos = Events::GetCursorPos();

	// if (camera_info_map.find(entity) == camera_info_map.end()) {
	// 	camera_info_map[entity] = Info{};
	// }

	// auto& info = camera_info_map[entity];

	// toggle = info.toggle;
	// scrollspeed = info.scrollspeed;

	if (camera.width != last_width || camera.height != last_height) {
		last_width = camera.width;
		last_height = camera.height;

		camera.lastx = camera.width / 2;
		camera.lasty = camera.height / 2;

		camera.first_mouse = true;

		camera.projection = glm::perspective(glm::radians(camera.fov), (float)camera.width / camera.height, camera.c_near, camera.c_far);
	}

	if (Events::IsButtonPressed(SDL_BUTTON_MIDDLE)) {
		if (camera.first_mouse) {
			camera.lastx = cursor_pos.x;
			camera.lasty = cursor_pos.y;
			camera.first_mouse = false;
		}

		transform.rotation.y -= (cursor_pos.x - camera.lastx) * camera.sensitivity;
		transform.rotation.x += (camera.lasty - cursor_pos.y) * camera.sensitivity;

		camera.lastx = cursor_pos.x;
		camera.lasty = cursor_pos.y;
	} else {
		camera.first_mouse = true;
	}

	const auto& quaternion = transform.GetRotationQuat();

	camera.front = glm::normalize(quaternion * camera.world_front);
	camera.up = glm::normalize(quaternion * camera.world_up);

	if (Events::IsMouseScrollingUp())
		camera.position += camera.front * float(scrollspeed * TimeStep::dt);
	if (Events::IsMouseScrollingDown())
		camera.position -= camera.front * float(scrollspeed * TimeStep::dt);

	float distance = glm::length(camera.position);
	scrollspeed = distance / 10;
	camera.position = distance * -camera.front;

	static glm::vec3 delta;
	static glm::vec3 initpos;

	if (Events::IsButtonPressed(SDL_BUTTON_LEFT) && Events::IsKeyPressed(SDL_SCANCODE_LALT)) {
		glm::vec4 ray_clip = glm::vec4(norm_cursor_pos.x, norm_cursor_pos.y, -1.0, 1.0);
		glm::vec4 ray_eye = glm::inverse(camera.projection) * ray_clip;
		ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		glm::vec3 ray_wor = glm::inverse(camera.view) * ray_eye;
		ray_wor = glm::normalize(ray_wor);

		float denom = glm::dot(camera.front, ray_wor);
		float t = -glm::dot((camera.front * distance), camera.front) / denom;
		glm::vec3 pos = ray_wor * t + (camera.offset + camera.position);

		if (!toggle)
			initpos = pos;

		delta = pos - initpos;
		toggle = true;
	}

	camera.view = glm::lookAt(camera.position + camera.offset + delta, camera.position + camera.offset + delta + camera.front, camera.up);

	if (toggle && !Events::IsButtonPressed(SDL_BUTTON_LEFT) && Events::IsKeyPressed(SDL_SCANCODE_LALT)) {
		camera.offset += delta;
		toggle = false;
		delta = glm::vec3();
	}
}
