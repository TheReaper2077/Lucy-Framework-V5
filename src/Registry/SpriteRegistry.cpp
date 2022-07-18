#include "SpriteRegistry.h"

lgl::Texture* lucy::SpriteRegistry::GetTexture(const std::string& filename) {
	LoadTexture(filename.substr(filename.find_last_of('\\') + 1, filename.find_last_of(".") - 1 - filename.find_last_of('\\')), filename, uuids::to_string(uuids::uuid_system_generator{}()));
}

lgl::Texture* lucy::SpriteRegistry::GetTextureById(const std::string& id) {
	if (texture_store.find(id) == texture_store.end())
		return nullptr;
	
	return &texture_store[id].texture;
}

lgl::Texture* lucy::SpriteRegistry::LoadTexture(const std::string& name, const std::string& filename, const std::string& id) {
	texture_store[id] = {};
	texture_store[id].filename = filename;
	texture_store[id].name = name;
	texture_store[id].texture = {};

	auto& texture = texture_store[id].texture;

	texture.Bind();
	texture.LoadTexture(filename.c_str());
	texture.UnBind();

	return &texture;
}
