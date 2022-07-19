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

	AddMesh("test", mesh);
}

bool lucy::MeshRegistry::Contains(std::string name) {
	return (mesh_registry.find(name) != mesh_registry.end());
}

lucy::Mesh* lucy::MeshRegistry::GetMesh(std::string name) {
	if (!Contains(name)) return nullptr;

	return &mesh_registry[name];
}

void lucy::MeshRegistry::AddMesh(std::string name, Mesh mesh) {
	mesh_registry[name] = mesh;
}

