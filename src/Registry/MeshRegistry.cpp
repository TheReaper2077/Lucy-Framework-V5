#include "MeshRegistry.h"

static auto& registry = lucy::Registry::Instance();

bool lucy::MeshRegistry::Contains(std::string name) {
	return (registry.find(name) != registry.end());
}

lucy::Mesh& lucy::MeshRegistry::GetMesh(std::string name) {
	return registry[name];
}

void lucy::MeshRegistry::AddMesh(std::string name, Mesh mesh) {
	registry[name] = mesh;
}
