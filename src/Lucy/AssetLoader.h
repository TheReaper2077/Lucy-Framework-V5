#pragma once

#include <string>
#include <assimp/Importer.hpp>

namespace lucy {
	struct AssetLoader {
	private:
		Assimp::Importer* importer = nullptr;

		#define self Instance()

		static AssetLoader* Instance() {
			static AssetLoader instance;
			return &instance;
		}

	public:
		static void Initialize();

		static lgl::Texture* CreateTexture();
		static Mesh* CreateMesh();
		static Material* CreateMaterial();

		static void LoadMesh(std::string filename);
		static void LoadMaterial(std::string filename);
	};
}