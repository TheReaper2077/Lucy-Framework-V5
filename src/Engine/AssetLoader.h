#pragma once

#include <Structures/Structures.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lucy {
	struct AssetLoader {
	private:
		Assimp::Importer* importer = nullptr;

		static AssetLoader& Instance() {
			static AssetLoader instance;
			return instance;
		}

	public:
		AssetLoader() {}

		static void Init();
		static const aiScene* Import(std::string filepath, uint32_t flags = 0);
	};
}