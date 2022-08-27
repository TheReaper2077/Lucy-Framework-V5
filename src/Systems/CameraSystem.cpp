#include "CameraSystem.h"
#include <Lucy/ECS.h>
#include <Lucy/Lucy.h>
#include <iostream>
#include <Structures/Structures.h>

static auto& registry = lucy::Registry::Instance();
static auto& window = registry.store<lucy::Window>();
static auto& state = registry.store<lucy::State>();
static bool toggle = false;
static float scrollspeed = .75;

void lucy::System::CameraSystem() {
	for (auto [entity, transform, camera]: registry.view<Transform, Camera>().each()) {
		if (!camera.enable);

		camera.update(entity, transform, camera);
	}
}
