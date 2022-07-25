#pragma once

#include <Engine/ECS.h>
#include <Components/Components.h>
#include <memory>
#include <Engine/AssetLoader.h>

namespace lucy {
	struct MeshRegistry {
	private:
		struct MeshContainer {
			Mesh mesh;
			std::string name;
		};

	public:
		std::unordered_map<std::string, MeshContainer> mesh_registry;

		MeshRegistry() {}

		void Init();
		std::string AddMesh(std::string name, const Mesh& mesh, uuid id = GetID());
		std::string AddMesh(std::string name, aiMesh* ai_mesh, uuid id = GetID());
		Mesh* GetMesh(const std::string& id);
	};
}