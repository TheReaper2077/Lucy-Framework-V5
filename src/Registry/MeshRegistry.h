#pragma once

#include <Engine/ECS.h>
#include <Components/Components.h>

namespace lucy {
	struct MeshRegistry {
		std::unordered_map<std::string, Mesh> registry;

		MeshRegistry() {}

		bool Contains(std::string name);
		
		Mesh& GetMesh(std::string name);

		void AddMesh(std::string name, Mesh mesh);
	};
}