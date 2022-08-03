#include "Functions.h"

void lucy::Functions::SetCameraEntity(const Entity& entity) {
	main_camera = entity;
}

lucy::Entity lucy::Functions::GetCameraEntity() {
	return main_camera;
}

void lucy::Functions::EnableDebugRender(bool enable) {
	enable_debug_render = enable;
}
