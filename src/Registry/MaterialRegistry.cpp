#include "MaterialRegistry.h"

void lucy::MaterialRegistry::Init() {
	
}

std::string lucy::MaterialRegistry::AddMaterial(const Material& material, std::string id) {
	material_registry[id] = material;

	return id;
}

lucy::Material* lucy::MaterialRegistry::GetMaterial(const std::string& id) {
	if (material_registry.find(id) == material_registry.end())
		return nullptr;
	
	return &material_registry[id];
}
