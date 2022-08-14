#pragma once

#include <Engine/ECS.h>
#include <Components/Components.h>
#include <memory>
#include <Engine/AssetLoader.h>

namespace lucy {
	struct MeshRegistry {
	public:
		std::unordered_map<uuid, Mesh> mesh_registry;

		MeshRegistry() {}

		void Init();
		std::string AddMesh(const Mesh& mesh, uuid id = GetID());
		std::string AddMesh(aiMesh* ai_mesh, uuid id = GetID());
		Mesh* GetMesh(const std::string& id);
		std::string GetMeshID(Mesh* mesh);
	};
}