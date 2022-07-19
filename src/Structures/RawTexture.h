#pragma once

#include <LucyGL/LucyGL.h>
#include <string>

namespace lucy {
	struct RawTexture {
		lgl::Texture* texture = nullptr;
		std::string name = "New Texture", filename = "", id;

		RawTexture() {}
	};
}