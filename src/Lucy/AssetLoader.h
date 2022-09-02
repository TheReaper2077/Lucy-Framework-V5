#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <LucyGL/LucyGL.h>
#include <Structures/Structures.h>
#include <unordered_map>
#include <LucyUtil/LucyUtil.h>

namespace lucy {
	struct Assets {
	private:
		Assimp::Importer* importer = nullptr;

		#define self Instance()

		static Assets* Instance() {
			static Assets instance;
			return &instance;
		}

		enum PTR_TYPE {
			Material,
			Texture,
			Mesh,

			PTR_TYPE_COUNT
		};

		// std::map<LUTIL_UUID, PTR_TYPE> asset_type;
		// std::vector<LUTIL_UUID, void*> asset_store;
		// std::unordered_map<std::string, LUTIL_UUID> asset_id_map;

	public:
		static void Initialize();

		static lgl::Texture* CreateTexture();

		static void GetLoadedMeshes();
		static void Load(std::string filename);
		static void LoadMaterial(std::string filename);
	};
}