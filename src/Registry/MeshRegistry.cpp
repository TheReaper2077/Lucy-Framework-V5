#include "MeshRegistry.h"

static auto& registry = lucy::Registry::Instance();

void lucy::MeshRegistry::Init() {
	Mesh mesh;

	mesh.positions = {
		{ -0.5, -0.5, -0.5, },
		{ 0.5, -0.5, -0.5, },
		{ 0.5,  0.5, -0.5, },
		{ 0.5,  0.5, -0.5, },
		{ -0.5,  0.5, -0.5, },
		{ -0.5, -0.5, -0.5, },
	};

	mesh.colors = {
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
	};

	mesh.normals = {
		{0.0,  0.0, -1.0},
		{0.0,  0.0, -1.0},
		{0.0,  0.0, -1.0},
		{0.0,  0.0, -1.0},
		{0.0,  0.0, -1.0},
		{0.0,  0.0, -1.0},
	};

	mesh.Transfer();
	AddMesh("plane", mesh);
}

lucy::Mesh* lucy::MeshRegistry::GetMesh(const std::string& id) {
	if (mesh_registry.find(id) == mesh_registry.end()) return nullptr;

	return &mesh_registry[id].mesh;
}

std::string lucy::MeshRegistry::AddMesh(std::string name, const Mesh& mesh, uuid id) {
	mesh_registry[id] = MeshContainer { mesh, name };

	return id;
}

std::string lucy::MeshRegistry::AddMesh(std::string name, aiMesh* ai_mesh, uuid id) {
	mesh_registry[id] = MeshContainer { Mesh(ai_mesh), name };

	return id;
}
