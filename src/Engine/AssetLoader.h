#pragma once

#include <Structures/Structures.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lucy {
	struct AssetLoader {
	private:
		Assimp::Importer* importer = nullptr;

	public:
		AssetLoader() {}

		void Init();
		const Mesh& LoadMesh(std::string filename);
		const Mesh& LoadSubMesh(std::string filename);
		const Material& LoadMaterial(std::string filename);
	};
}