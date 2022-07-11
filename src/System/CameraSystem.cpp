#include "CameraSystem.h"
#include <Engine/ECS.h>
#include <Engine/TimeStep.h>
#include <Engine/Window.h>
#include <Engine/Events.h>
#include <Components/Components.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

static auto& registry = lucy::Registry::Instance();
static auto& timestep = registry.store<lucy::TimeStep>();
static auto& window = registry.store<lucy::Window>();
static auto& events = registry.store<lucy::Events>();

void lucy::CameraSystem::Update() {
	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		if (camera.width != window.size.x || camera.height != window.size.y) {
			camera.width = window.size.x;
			camera.height = window.size.y;

			camera.lastx = camera.width / 2;
			camera.lasty = camera.height / 2;

			camera.first_mouse = true;

			camera.projection = glm::perspective(glm::radians(camera.fov), (float)camera.width / camera.height, camera.c_near, camera.c_far);
		}

		FPSView(entity);
	}
}

void lucy::CameraSystem::FPSView(Entity entity) {
	auto& transform = registry.get<Transform>(entity);
	auto& camera = registry.get<Camera>(entity);

	if (events.IsButtonPressed(SDL_BUTTON_MIDDLE)) {
		auto pos = events.GetCursorPos();

		if (camera.first_mouse) {
			camera.lastx = pos.x;
			camera.lasty = pos.y;
			camera.first_mouse = false;
		}

		transform.rotation.y -= (pos.x - camera.lastx) * camera.sensitivity;
		transform.rotation.x += (camera.lasty - pos.y) * camera.sensitivity;

		camera.lastx = pos.x;
		camera.lasty = pos.y;
	} else {
		camera.first_mouse = true;
	}

	const auto& quaternion = transform.GetRotationQuat();

	camera.front = glm::normalize(quaternion * camera.world_front);
	camera.up = glm::normalize(quaternion * camera.world_up);

	if (events.IsButtonPressed(SDL_BUTTON_MIDDLE)) {
		const auto& dt = timestep.GetTimeStep();
		const float speed = 0.5 * dt;

		if (events.IsKeyPressed(SDL_SCANCODE_W))
			transform.translation += camera.front * speed;
		if (events.IsKeyPressed(SDL_SCANCODE_S))
			transform.translation -= camera.front * speed;
		if (events.IsKeyPressed(SDL_SCANCODE_A))
			transform.translation -= glm::normalize(glm::cross(camera.front, camera.up)) * speed;
		if (events.IsKeyPressed(SDL_SCANCODE_D))
			transform.translation += glm::normalize(glm::cross(camera.front, camera.up)) * speed;
		if (events.IsKeyPressed(SDL_SCANCODE_LSHIFT))
			transform.translation -= camera.up * speed;
		if (events.IsKeyPressed(SDL_SCANCODE_SPACE))
			transform.translation += camera.up * speed;
	}

	camera.view = glm::lookAt(transform.translation, transform.translation + camera.front, camera.up);
}

void lucy::CameraSystem::EditorView(Entity entity) {
	
}
