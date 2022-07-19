#pragma once

#include <Structures/Structures.h>
#include <unordered_map>

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>

namespace lucy {
	struct MaterialRegistry {
		std::unordered_map<std::string, Material> material_registry;

		MaterialRegistry() {}

		void Init();
		std::string AddMaterial(const Material& material, std::string id = uuids::to_string(uuids::uuid_system_generator{}()));
		Material* GetMaterial(const std::string& id);
	};
}