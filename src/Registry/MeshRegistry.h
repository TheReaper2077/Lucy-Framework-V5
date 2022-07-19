#pragma once

#include <Engine/ECS.h>
#include <Components/Components.h>
#include <memory>

namespace lucy {
	struct MeshRegistry {
	private:
		std::unordered_map<std::string, Mesh> mesh_registry;

	public:
		MeshRegistry() {}

		void Init();
		bool Contains(std::string name);		
		Mesh* GetMesh(std::string name);
		void AddMesh(std::string name, Mesh mesh);
		template <typename ...Args>
		void AddMesh(std::string name, Args ...args) {
			mesh_registry = Mesh{args...};
		}
	};
}