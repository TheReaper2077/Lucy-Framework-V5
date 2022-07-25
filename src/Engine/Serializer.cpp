#include "Serializer.h"
#include "ToYAML.h"
#include "ECS.h"
#include <iostream>
#include <Registry/Registry.h>
#include <Components/Components.h>
#include <Structures/Structures.h>

static auto& registry = lucy::Registry::Instance();

void lucy::SerializeEntities(YAML::Emitter& out) {
	out << YAML::BeginMap;

	out << YAML::Key << "Entities";
	out << YAML::Value;
	out << YAML::BeginSeq;

	for (auto [entity, tag]: registry.view<Tag>().each()) {
		out << YAML::BeginMap;

		out << YAML::Key << "Tag";
		out << YAML::Value << &tag;

		auto* transform = registry.try_get<Transform>(entity);
		if (transform != nullptr) {
			out << YAML::Key << "Transform";
			out << YAML::Value << transform;
		}

		auto* light = registry.try_get<Light>(entity);
		if (light != nullptr) {
			out << YAML::Key << "Light";
			out << YAML::Value << light;
		}

		auto* camera = registry.try_get<Camera>(entity);
		if (camera != nullptr) {
			out << YAML::Key << "Camera";
			out << YAML::Value << camera;
		}

		auto* spriterenderer = registry.try_get<SpriteRenderer>(entity);
		if (spriterenderer != nullptr) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::Value << spriterenderer;
		}

		auto* meshrenderer = registry.try_get<MeshRenderer>(entity);
		if (meshrenderer != nullptr) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::Value << meshrenderer;
		}

		out << YAML::EndMap;
	}

	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::cout << out.c_str();
}
