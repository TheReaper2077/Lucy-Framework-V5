#pragma once

#include <Structures/Structures.h>
#include <unordered_map>
#include <Engine/UUID.h>

namespace lucy {
	struct MaterialRegistry {
		std::unordered_map<uuid, Material> material_registry;

		MaterialRegistry() {}

		void Init();
		std::string AddMaterial(const Material& material, uuid id = GetID());
		Material* GetMaterial(const std::string& id);
	};
}