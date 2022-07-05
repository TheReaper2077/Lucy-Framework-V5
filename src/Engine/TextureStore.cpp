#include "TextureStore.h"
#include <assert.h>

bool lucy::TextureStore::SlotAvaliable() {
	return (next_unit <= 8);
}

uint32_t lucy::TextureStore::operator[](lgl::Texture* texture) {
	return operator[](texture->id);
}

void lucy::TextureStore::Bind() {
	for (auto& pair: texture_unit_map) {
		lgl::BindTextureUnit(pair.first, pair.second);
	}
}

uint32_t lucy::TextureStore::operator[](lgl::TextureId texture) {
	if (texture_unit_map.find(texture) == texture_unit_map.end()) {
		assert(SlotAvaliable());
		texture_unit_map[texture] = next_unit++;
	}

	return texture_unit_map[texture];
}