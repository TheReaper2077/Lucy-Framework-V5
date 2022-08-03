#include "Application.h"
#include <Registry/Registry.h>
#include <Components/Components.h>
#include <iostream>
#include <Engine/Functions.h>

lucy::Entity player_entity, camera_entity;

void InitApplication(lucy::Registry& registry) {	
	auto& timestep = registry.store<lucy::TimeStep>();
	auto& events = registry.store<lucy::Events>();
	auto& meshregistry = registry.store<lucy::MeshRegistry>();
	auto& spriteregistry = registry.store<lucy::SpriteRegistry>();
	auto& materialregistry = registry.store<lucy::MaterialRegistry>();
	auto& functions = registry.store<lucy::Functions>();
	auto& window = registry.store<lucy::Window>();

	static lucy::Sprite sprite;
	sprite.raw_texture = spriteregistry.GetTexture("D:\\C++\\Lucy Framework V5\\assets\\Redstone.PNG");

	player_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(player_entity, "Player");
		registry.emplace<lucy::Transform>(player_entity, glm::vec3(0, -50, 0), glm::vec3(0, 0, 45), glm::vec3(50, 50, 0));
		auto& spriterenderer = registry.emplace<lucy::SpriteRenderer>(player_entity);
		spriterenderer.color = { 0, 1, 1, 1 };

		auto& rigidbody2D = registry.emplace<lucy::Rigidbody2D>(player_entity);
		rigidbody2D.type = lucy::DYNAMIC;
		// rigidbody2D.fixed_rotation = false;

		auto& bc2d = registry.emplace<lucy::BoxCollider2D>(player_entity);
		bc2d.use_scale = true;
	}

	lucy::Entity floor_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(floor_entity, "Floor");
		registry.emplace<lucy::Transform>(floor_entity, glm::vec3(0, -500, 0), glm::vec3(0, 0, 0), glm::vec3(500, 20, 0));
		auto& spriterenderer = registry.emplace<lucy::SpriteRenderer>(floor_entity);
		spriterenderer.color = { 1, 0, 0, 1 };

		auto& rigidbody2D = registry.emplace<lucy::Rigidbody2D>(floor_entity);
		rigidbody2D.type = lucy::STATIC;

		auto& bc2d = registry.emplace<lucy::BoxCollider2D>(floor_entity);
		bc2d.use_scale = true;
	}

	camera_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(camera_entity, "CameraFPS");
		registry.emplace<lucy::Transform>(camera_entity, glm::vec3(0, 0, 1));
		auto& camera = registry.emplace<lucy::Camera>(camera_entity, lucy::ViewMode_None, true);
		camera.type = lucy::ORTHOGRAPHIC;
		functions.main_camera = camera_entity;
		camera.width = window.size.x;
		camera.height = window.size.y;
	}
}

void UpdateApplication(lucy::Registry& registry) {

}