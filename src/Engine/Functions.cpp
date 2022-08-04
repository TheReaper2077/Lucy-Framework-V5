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

void lucy::Functions::PlayPhysics() {
	physics_play = true;
	physics_pause = false;
	physics_stop = false;
}

void lucy::Functions::StopPhysics() {
	physics_play = false;
	physics_pause = false;
	physics_stop = true;
}

void lucy::Functions::PausePhysics() {
	physics_play = false;
	physics_pause = true;
	physics_stop = false;
}

bool lucy::Functions::IsPhysicsPlaying() {
	return physics_play;
}

bool lucy::Functions::IsPhysicsStopped() {
	return physics_stop;
}

bool lucy::Functions::IsPhysicsPaused() {
	return physics_pause;
}
