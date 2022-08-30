#pragma once

#include <LucyUtil/LucyUtil.h>
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

		std::unordered_map<LUTIL_UUID, MeshContainer> mesh_store;

		void Add(Mesh* mesh, const std::string& name, const std::string& filepath, const LUTIL_UUID& id = LUTIL_GENERATE_UUID);
		const LUTIL_UUID& GetMeshID(Mesh* mesh);
		lucy::Mesh* GetByID(const LUTIL_UUID& id);
		lucy::Mesh* GetByFilepath(const std::string& filepath);
		lucy::Mesh* GetByFilepathAndName(const std::string& filepath, const std::string& name);
		lucy::Mesh* GetByName(const std::string& name);
	};
}