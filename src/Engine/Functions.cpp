#include "Functions.h"

void lucy::Functions::SetCameraEntity(const Entity& entity) {
	main_camera = entity;
}

lucy::Entity lucy::Functions::GetCameraEntity() {
	return main_camera;
}

void lucy::Functions::EnableDebugRender(bool enable) {
	enable_physics_object_render = enable;
}

void lucy::Functions::PlayPhysics() {
	state = PLAY;
}

void lucy::Functions::StopPhysics() {
	state = STOP;
}

void lucy::Functions::PausePhysics() {
	state = PAUSE;
}

bool lucy::Functions::IsPhysicsPlaying() {
	return (state == PLAY);
}

bool lucy::Functions::IsPhysicsStopped() {
	return (state == STOP);
}

bool lucy::Functions::IsPhysicsPaused() {
	return (state == PAUSE);
}
