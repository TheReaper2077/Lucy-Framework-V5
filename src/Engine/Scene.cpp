#include "Scene.h"

static auto& registry = lucy::Registry::Instance();

void lucy::Scene::Play() {
	game_state = PLAY;
}

void lucy::Scene::Pause() {
	game_state = PAUSE;
}

void lucy::Scene::Stop() {
	if (IsPlaying()) {
		for (auto entity: temporary_entities) {
			registry.destroy(entity);
		}
	}

	game_state = STOP;
}

bool lucy::Scene::IsPlaying() {
	return (game_state == PLAY);
}

bool lucy::Scene::IsPaused() {
	return (game_state == PAUSE);
}

bool lucy::Scene::IsStopped() {
	return (game_state == STOP);
}

