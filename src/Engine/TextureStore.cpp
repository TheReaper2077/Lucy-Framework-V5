#include "TextureStore.h"
#include <assert.h>

bool lucy::TextureStore::slotavaliable() {
	return (next_unit <= 8);
}

uint32_t lucy::TextureStore::operator[](lgl::Texture* texture) {
	return operator[](texture->id);
}

void lucy::TextureStore::bind() {
	for (auto& pair: texture_unit_map) {
		lgl::BindTextureUnit(pair.first, pair.second);
	}
}

void lucy::TextureStore::clear() {
	texture_unit_map.clear();
	next_unit = 0;
}

uint32_t lucy::TextureStore::operator[](lgl::TextureId texture) {
	if (texture_unit_map.find(texture) == texture_unit_map.end()) {
		assert(slotavaliable());
		texture_unit_map[texture] = next_unit++;
	}

	return texture_unit_map[texture];
}