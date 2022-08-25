#include "SpriteRegistry.h"

lucy::RawTexture* lucy::SpriteRegistry::GetTexture(const std::string& filename) {
	return LoadTexture(filename.substr(filename.find_last_of('\\') + 1, filename.find_last_of(".") - 1 - filename.find_last_of('\\')), filename, GetID());
}

lucy::RawTexture* lucy::SpriteRegistry::GetTexturebyId(const std::string& id) {
	if (texture_store.find(id) != texture_store.end())
		return &texture_store[id];
	
	return nullptr;
}

// lucy::Sprite* lucy::SpriteRegistry::GetSpritebyId(const std::string& id) {
// 	for (auto& pair: sprite_store) {
// 		for (auto& sprite: pair.second) {
// 			if (id == sprite.id) {
// 				return &sprite;
// 			}
// 		}
// 	}

// 	return nullptr;
// }

lucy::RawTexture* lucy::SpriteRegistry::GetTexture(const std::string& filename, int x, int y, int w, int h) {
	return LoadTextureArray(filename.substr(filename.find_last_of('\\') + 1, filename.find_last_of(".") - 1 - filename.find_last_of('\\')), filename, x, y, w, h, GetID());
}

lgl::Texture* lucy::SpriteRegistry::GetNullTexture() {
	static lgl::Texture* texture = nullptr;

	if (texture == nullptr) {
		texture = new lgl::Texture();
		texture->Bind();
		texture->LoadTexture(nullptr);
		texture->UnBind();
	}

	return texture;
}

lucy::RawTexture* lucy::SpriteRegistry::LoadTexture(const std::string& name, const std::string& filename, const uuid& id) {
	for (auto& pair: texture_store) {
		if (pair.second.filename == filename)
			return &pair.second;
	}

	if (texture_store.find(id) == texture_store.end()) {
		texture_store[id] = {};

		texture_store[id].filename = filename;
		texture_store[id].name = name;
		texture_store[id].texture = lgl::MakeTexture(lgl::TEXTURE_2D);
		texture_store[id].id = id;

		auto* texture = texture_store[id].texture;

		texture->Bind();
		texture->LoadTexture(filename.c_str());
		texture->UnBind();

		return &texture_store[id];
	}

	return &texture_store[id];
}

lucy::RawTexture* lucy::SpriteRegistry::LoadTextureArray(const std::string& name, const std::string& filename, int x, int y, int w , int h, const uuid& id) {
	for (auto& pair: texture_store) {
		if (pair.second.filename == filename)
			return &pair.second;
	}

	if (texture_store.find(id) == texture_store.end()) {
		texture_store[id] = {};

		texture_store[id].filename = filename;
		texture_store[id].name = name;
		texture_store[id].texture = lgl::MakeTexture(lgl::TEXTURE_2D_ARRAY);
		texture_store[id].id = id;

		auto* texture = texture_store[id].texture;

		texture->Bind();
		texture->LoadSpriteSheet(filename.c_str(), x, y, w, h);
		texture->UnBind();

		return &texture_store[id];
	}
}

void lucy::SpriteRegistry::GenerateSprites(RawTexture* raw_texture) {
	if (raw_texture == nullptr)	return;
	if (raw_texture->texture == nullptr) return;

	int i = 0;
	for (int x = 0; x < raw_texture->texture->tile_x; x += raw_texture->texture->tile_w) {
		for (int y = 0; y < raw_texture->texture->tile_y; y += raw_texture->texture->tile_h) {
			// Sprite sprite;
			// sprite.id = GetID();
			// sprite.raw_texture = raw_texture;
			// sprite.idx = 
			// sprite_store[GetID()]
		}
	}
}
