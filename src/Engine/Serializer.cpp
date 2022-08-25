#include <iostream>
#include "Functions.h"
#include "Window.h"
#include "ECS.h"
#include "Serializer.h"
#include "ToYAML.h"
#include "Util.h"

static auto& registry = lucy::Registry::Instance();

bool lucy::Util::SerializeEntities(const std::string& filename) {
	YAML::Emitter out;
	out << YAML::BeginSeq;
	for (auto entity: registry.view<Tag>()) {
		out << YAML::BeginMap;

		auto [
			tag, transform, camera, light, spriterenderer, meshrenderer
		] = registry.try_get<Tag, Transform, Camera, Light, SpriteRenderer, MeshRenderer>(entity);

		if (tag != nullptr) {
			out << YAML::Key << "Tag";
			out << YAML::Value << tag;
		}
		if (transform != nullptr) {
			out << YAML::Key << "Transform";
			out << YAML::Value << transform;
		}
		if (camera != nullptr) {
			out << YAML::Key << "Camera";
			out << YAML::Value << camera;
		}
		if (light != nullptr) {
			out << YAML::Key << "Light";
			out << YAML::Value << light;
		}
		if (spriterenderer != nullptr) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::Value << spriterenderer;
		}
		if (meshrenderer != nullptr) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::Value << meshrenderer;
		}
		out << YAML::EndMap;
	}
	out << YAML::EndSeq;

	return util::write_file(filename, out.c_str());
}

lucy::Entity is_entity_present(const std::string& id) {
	for (auto [entity, tag]: registry.view<lucy::Tag>().each()) {
		if (tag.id == id) return entity;
	}

	return (lucy::Entity)0;
}


void lucy::Util::DeserializeEntities(const std::string& filename) {
	std::string src = util::read_file(filename);

	if (src == "") return;

	YAML::Node scene = YAML::LoadFile(filename);

	for (size_t i = 0; i < scene.size(); i++) {
		Entity entity;

		if (scene[i]["Tag"]) {
			auto tag = scene[i]["Tag"].as<Tag>();

			entity = is_entity_present(tag.id);
			
			if (entity == (Entity)0)
				entity = registry.create();

			registry.emplace<Tag>(entity, tag);
		} else continue;

		if (scene[i]["Transform"]) {
			registry.emplace<Transform>(entity, scene[i]["Transform"].as<Transform>());
		} else if (registry.try_get<Transform>(entity) != nullptr) {
			registry.remove<Transform>(entity);
		}
		if (scene[i]["Camera"]) {
			auto camera = scene[i]["Camera"].as<Camera>();
			registry.emplace<Camera>(entity, camera);
			if (camera.enable)
				registry.store<Functions>().main_camera = entity;
		} else if (registry.try_get<Camera>(entity) != nullptr) {
			registry.remove<Camera>(entity);
		}
		if (scene[i]["Light"]) {
			registry.emplace<Light>(entity, scene[i]["Light"].as<Light>());
		} else if (registry.try_get<Light>(entity) != nullptr) {
			registry.remove<Light>(entity);
		}
		if (scene[i]["SpriteRenderer"]) {
			registry.emplace<SpriteRenderer>(entity, scene[i]["SpriteRenderer"].as<SpriteRenderer>());
		} else if (registry.try_get<SpriteRenderer>(entity) != nullptr) {
			registry.remove<SpriteRenderer>(entity);
		}
		if (scene[i]["MeshRenderer"]) {
			registry.emplace<MeshRenderer>(entity, scene[i]["MeshRenderer"].as<MeshRenderer>());
		} else if (registry.try_get<MeshRenderer>(entity) != nullptr) {
			registry.remove<MeshRenderer>(entity);
		}
	}
}

// bool lucy::Util::SerializeSpriteRegistry(const std::string& filename) {
// 	auto& spriteregistry = registry.store<SpriteRegistry>();

// 	YAML::Emitter out;
// 	out << YAML::BeginMap;
// 		out << YAML::Key << "Textures";
// 		out << YAML::Value;
// 		out << YAML::BeginSeq;

// 		for (auto& pair: spriteregistry.texture_store) {
// 			out << pair.second;
// 		}

// 		out << YAML::EndSeq;

// 		out << YAML::Key << "Sprites";
// 		out << YAML::Value;
// 		out << YAML::BeginSeq;

// 		for (auto& pair: spriteregistry.sprite_store) {
// 			out << &pair.second;
// 		}

// 		out << YAML::EndSeq;
// 	out << YAML::EndMap;

// 	return WriteFile(filename, out.c_str());
// }

// void lucy::Util::DeserializeSpriteRegistry(const std::string& filename) {
// 	auto& spriteregistry = registry.store<SpriteRegistry>();

// 	std::string src = ReadFile(filename);

// 	if (src == "") return;

// 	YAML::Node scene = YAML::LoadFile(filename);

// 	for (int i = 0; i != scene["Textures"].size(); i++) {
// 		auto filename = scene["Textures"][i]["filename"].as<std::string>();
// 		auto name = scene["Textures"][i]["name"].as<std::string>();
// 		auto id = scene["Textures"][i]["id"].as<std::string>();

// 		spriteregistry.LoadTexture(name, filename, id);
// 	}

// 	for (int i = 0; i != scene["Sprites"].size(); i++) {
// 		lucy::Sprite sprite;

// 		sprite.id = scene["Sprites"][i]["id"].as<std::string>();
// 		sprite.raw_texture_id = scene["Sprites"][i]["raw_texture_id"].as<std::string>();
// 		sprite.name = scene["Sprites"][i]["name"].as<std::string>();
// 		sprite.uv0 = scene["Sprites"][i]["uv0"].as<glm::vec2>();
// 		sprite.uv1 = scene["Sprites"][i]["uv1"].as<glm::vec2>();
// 		sprite.idx = scene["Sprites"][i]["idx"].as<int>();

// 		spriteregistry.sprite_store[sprite.id] = sprite;
// 	}
// }
