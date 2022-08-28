#pragma once

#include <Structures/Structures.h>
#include <unordered_map>
#include <map>
#include <string>

namespace lucy {
	struct MeshRegistry {
		struct MeshContainer {
			Mesh* mesh = nullptr;
			std::string name;
			std::string filepath;
		};

		std::unordered_map<std::string, MeshContainer> mesh_store;

		void Add(Mesh* mesh, const std::string& name, const std::string& filepath, const std::string& id = GetID());
		const std::string& GetMeshID(Mesh* mesh);
		lucy::Mesh* GetByID(const std::string& id);
		lucy::Mesh* GetByFilepath(const std::string& filename);
		lucy::Mesh* GetByName(const std::string& name);
	};
}