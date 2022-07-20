#include "Functions.h"
#include <Components/Components.h>
#include <Engine/UUID.h>

static auto& registry = lucy::Registry::Instance();

bool is_name_present(std::string name) {
	for (auto [entity, tag]: registry.view<lucy::Tag>().each()) {
		if (tag.name == name) {
			return true;
		}
	}

	return false;
}

std::string lucy::Functions::GetName(std::string name) {
	std::string result = name;

	for (int i = 1; is_name_present(result); i++) {
		result = name + '(' + std::to_string(i) + ')';
	}

	return result;
}

lucy::Entity lucy::Functions::CreateEmptyEntity() {
	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, GetName("Empty"), GetID());
	registry.emplace<lucy::Transform>(entity);

	return entity;
}

lucy::Entity lucy::Functions::CreateLightEntity() {
	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, GetName("Light"), GetID());
	registry.emplace<lucy::Transform>(entity);
	registry.emplace<lucy::Light>(entity);

	return entity;
}

lucy::Entity lucy::Functions::CreateCameraEntity() {
	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, GetName("Camera"), GetID());
	registry.emplace<lucy::Transform>(entity);
	registry.emplace<lucy::Camera>(entity);

	return entity;
}

lucy::Entity lucy::Functions::CreateMeshEntity() {
	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, GetName("Mesh"), GetID());
	registry.emplace<lucy::Transform>(entity);
	registry.emplace<lucy::MeshRenderer>(entity);

	return entity;
}

lucy::Entity lucy::Functions::CreateSpriteEntity() {
	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, GetName("Sprite"), GetID());
	registry.emplace<lucy::Transform>(entity);
	registry.emplace<lucy::SpriteRenderer>(entity);

	return entity;
}

void lucy::Functions::Serialize() {
	
}

void lucy::Functions::Deserialize() {
	
}

void lucy::Functions::SerializeEntities() {
	
}

void lucy::Functions::DeserializeEntities() {
	
}

void lucy::Functions::StartPlaying() {
	playing = true;
	paused = false;
}

void lucy::Functions::StopPlaying() {
	playing = paused = false;
}

void lucy::Functions::PausePlaying() {
	paused = true;
}

bool lucy::Functions::IsPlaying() {
	return (playing && !paused);
}

bool lucy::Functions::IsPlayingPaused() {
	return paused;
}

