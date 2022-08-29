#include "MeshRegistry.h"

void lucy::MeshRegistry::Add(Mesh* mesh, const std::string& name, const std::string& filepath, const std::string& id) {
	assert(mesh_store.find(id) == mesh_store.end());

	mesh_store[id] = { mesh, name, filepath };
}

const std::string& lucy::MeshRegistry::GetMeshID(Mesh* mesh) {
	for (auto& pair: mesh_store) {
		if (pair.second.mesh == mesh)
			return pair.first;
	}

	return "";
}

lucy::Mesh* lucy::MeshRegistry::GetByID(const std::string& id) {
	if (mesh_store.find(id) == mesh_store.end())
		return nullptr;

	return mesh_store[id].mesh;
}

lucy::Mesh* lucy::MeshRegistry::GetByFilepath(const std::string& filepath) {
	for (auto& pair: mesh_store) {
		if (pair.second.filepath == filepath)
			return pair.second.mesh;
	}

	return nullptr;
}

lucy::Mesh* lucy::MeshRegistry::GetByFilepathAndName(const std::string& filepath, const std::string& name) {
	for (auto& pair: mesh_store) {
		if (pair.second.filepath == filepath && pair.second.name == name)
			return pair.second.mesh;
	}

	return nullptr;
}

lucy::Mesh* lucy::MeshRegistry::GetByName(const std::string& name) {
	for (auto& pair: mesh_store) {
		if (pair.second.name == name)
			return pair.second.mesh;
	}

	return nullptr;
}
