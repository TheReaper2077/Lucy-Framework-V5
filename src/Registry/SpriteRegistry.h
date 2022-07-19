#pragma once

#include <LucyGL/LucyGL.h>
#include <Structures/Structures.h>

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>

namespace lucy {
	struct SpriteRegistry {
		std::unordered_map<std::string, RawTexture> texture_store;
		std::unordered_map<std::string, lucy::Sprite> sprite_store;

		RawTexture* GetTexture(const std::string& filename);
		RawTexture* GetTextureById(const std::string& id);
		RawTexture* LoadTexture(const std::string& name, const std::string& filename, const std::string& id = uuids::to_string(uuids::uuid_system_generator{}()));

		std::string Serialize();
		bool Deserialize(const std::string& src);
	};
}