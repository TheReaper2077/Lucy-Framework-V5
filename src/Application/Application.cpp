#include "Application.h"
#include <Registry/Registry.h>
#include <Components/Components.h>
#include <iostream>

lucy::Sprite sprite;

void InitGame(lucy::Registry& registry) {	
	auto& timestep = registry.store<lucy::TimeStep>();
	auto& events = registry.store<lucy::Events>();
	auto& renderer = registry.store<lucy::Renderer>();
	auto& meshregistry = registry.store<lucy::MeshRegistry>();
	auto& spriteregistry = registry.store<lucy::SpriteRegistry>();
	auto& materialregistry = registry.store<lucy::MaterialRegistry>();
	auto& window = registry.store<lucy::Window>();

	sprite.raw_texture = spriteregistry.GetTexture("D:\\C++\\Lucy Framework V5\\assets\\Redstone.PNG");

	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, "Entity");
	registry.emplace<lucy::Transform>(entity, glm::vec3(0, 0, -1), glm::vec3(0, 0, 45), glm::vec3(1, 1, 1));
	registry.emplace<lucy::SpriteRenderer>(entity, sprite);

	auto camera_entity = registry.create();
	registry.emplace<lucy::Tag>(camera_entity, "CameraFPS");
	registry.emplace<lucy::Transform>(camera_entity, glm::vec3(0, 0, 1));
	registry.emplace<lucy::Camera>(camera_entity, lucy::ViewMode_None, true);
}

void UpdateGame(lucy::Registry& registry) {

}