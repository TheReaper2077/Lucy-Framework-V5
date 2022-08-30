#include "CameraSystem.h"
#include <Lucy/ECS.h>
#include <Lucy/Lucy.h>
#include <iostream>
#include <Structures/Structures.h>

static auto& registry = lucy::Registry::Instance();

void lucy::System::CameraSystem() {
	auto& engine_state = registry.store<lucy::State>();
	auto& window = registry.store<Window>();

	for (auto [entity, transform, camera]: registry.view<Transform, Camera>().each()) {
		if (!camera.enable);

		if (entity == engine_state.camera_entity) {
			camera.width = window.size.x;
			camera.height = window.size.y;
			camera.posx = window.pos.x;
			camera.posy = window.pos.y;

			camera.framebuffer = window.framebuffer;
		}

		camera.update(entity, transform, camera);
	}
}
