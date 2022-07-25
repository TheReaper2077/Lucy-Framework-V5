#include "MaterialRegistry.h"

void lucy::MaterialRegistry::Init() {
	
}

std::string lucy::MaterialRegistry::AddMaterial(const Material& material, std::string id) {
	material_registry[id] = material;

	return id;
}

std::string lucy::MaterialRegistry::AddMaterial(aiMaterial* ai_material, std::string id) {
	assert(ai_material != nullptr);

	material_registry[id] = Material(ai_material);

	return id;
}

lucy::Material* lucy::MaterialRegistry::GetMaterial(const std::string& id) {
	if (material_registry.find(id) == material_registry.end())
		return nullptr;

	return &material_registry[id];
}

std::string lucy::MaterialRegistry::GetMaterialID(Material* material) {
	if (material == nullptr) return "";

	for (auto& pair: material_registry) {
		if (&pair.second == material) {
			return pair.first;
		}
	}
}
