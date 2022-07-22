#pragma once

#include <LucyGL/LucyGL.h>
#include <Structures/Structures.h>
#include <Engine/UUID.h>

namespace lucy {
	struct SpriteRegistry {
		std::unordered_map<std::string, RawTexture> texture_store;
		std::unordered_map<std::string, lucy::Sprite> sprite_store;

		RawTexture* GetTexture(const std::string& filename);
		RawTexture* GetTexture();
		lgl::Texture* GetNullTexture();
		RawTexture* GetTextureById(const uuid& id);
		RawTexture* GetTextureByFilename(const std::string& filename);
		RawTexture* LoadTexture(const std::string& name, const std::string& filename, const uuid& id = GetID());

		std::string Serialize();
		bool Deserialize(const std::string& src);
	};
}