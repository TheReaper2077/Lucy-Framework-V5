#pragma once

#include <LucyGL/API.h>
#include <unordered_map>

namespace lucy {
	struct TextureStore {
	private:
		unsigned int next_unit = 0;
		std::unordered_map<lgl::TextureId, uint32_t> texture_unit_map;

	public:
		void Bind();
		bool SlotAvaliable();

		uint32_t operator[](lgl::Texture* texture);
		uint32_t operator[](lgl::TextureId texture);
	};
}