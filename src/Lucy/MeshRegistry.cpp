#include "MeshRegistry.h"

void lucy::MeshRegistry::Add(Mesh* mesh, const std::string& name, const std::string& filepath, const LUTIL_UUID& id) {
	assert(mesh_store.find(id) == mesh_store.end());

	mesh_store[id] = { mesh, name, filepath };
}

const LUTIL_UUID& lucy::MeshRegistry::GetMeshID(Mesh* mesh) {
	for (auto& pair: mesh_store) {
		if (pair.second.mesh == mesh)
			return pair.first;
	}

	return LUTIL_NULL_UUID;
}

lucy::Mesh* lucy::MeshRegistry::GetByID(const LUTIL_UUID& id) {
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
