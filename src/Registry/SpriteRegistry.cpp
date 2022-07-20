#include "SpriteRegistry.h"

lucy::RawTexture* lucy::SpriteRegistry::GetTexture(const std::string& filename) {
	return LoadTexture(filename.substr(filename.find_last_of('\\') + 1, filename.find_last_of(".") - 1 - filename.find_last_of('\\')), filename, GetID());
}

lgl::Texture* lucy::SpriteRegistry::GetNullTexture() {
	static lgl::Texture texture;

	texture.Bind();
	texture.LoadTexture(nullptr);
	texture.UnBind();

	return &texture;
}

lucy::RawTexture* lucy::SpriteRegistry::GetTextureById(const uuid& id) {
	if (texture_store.find(id) == texture_store.end())
		return nullptr;
	
	return &texture_store[id];
}

lucy::RawTexture* lucy::SpriteRegistry::LoadTexture(const std::string& name, const std::string& filename, const uuid& id) {
	if (texture_store.find(id) == texture_store.end()) {
		texture_store[id] = {};

		texture_store[id].filename = filename;
		texture_store[id].name = name;
		texture_store[id].texture = lgl::MakeTexture();
		texture_store[id].id = id;

		auto* texture = texture_store[id].texture;

		texture->Bind();
		texture->LoadTexture(filename.c_str());
		texture->UnBind();

		return &texture_store[id];
	}

	return &texture_store[id];
}
