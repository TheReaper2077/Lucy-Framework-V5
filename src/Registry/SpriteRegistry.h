#pragma once

#include <LucyGL/LucyGL.h>
#include <Structures/Structures.h>
#include <Engine/UUID.h>

namespace lucy {
	struct SpriteRegistry {
		std::unordered_map<std::string, RawTexture> texture_store;
		std::unordered_map<RawTexture*, std::unordered_map<std::string, lucy::Sprite>> sprite_store;

		lgl::Texture* GetNullTexture();

		RawTexture* GetTexture(const std::string& filename);
		RawTexture* GetTexturebyId(const std::string& id);
		Sprite* GetSpritebyId(const std::string& id);
		RawTexture* GetTexture(const std::string& filename, int x, int y, int w, int h);

		RawTexture* LoadTexture(const std::string& name, const std::string& filename, const uuid& id = GetID());
		RawTexture* LoadTextureArray(const std::string& name, const std::string& filename, int x, int y, int w , int h, const uuid& id = GetID());

		void GenerateSprites(RawTexture* raw_texture);
	};
}
