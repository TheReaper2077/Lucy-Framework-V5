#pragma once

#include <LucyGL/LucyGL.h>
#include <Structures/Structures.h>

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>

namespace lucy {
	struct SpriteRegistry {
		struct TextureCountainer {
			lgl::Texture* texture = nullptr;
			std::string name = "", filename = "";
		};

		typedef std::string tex_filename;

		std::unordered_map<std::string, TextureCountainer> texture_store;
		std::unordered_map<std::string, lucy::Sprite> sprite_store;

		lgl::Texture* GetTexture(const std::string& filename);
		lgl::Texture* GetTextureById(const std::string& id);

		lgl::Texture* LoadTexture(const std::string& name, const std::string& filename, const std::string& id = uuids::to_string(uuids::uuid_system_generator{}()));

		lucy::Sprite* LoadSprite();
		lucy::Sprite* GetSprite(std::string id);

		std::string Serialize();
		bool Deserialize(const std::string& src);
	};
}