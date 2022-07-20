#pragma once

#include <LucyGL/LucyGL.h>
#include <string>
#include <Engine/UUID.h>

namespace lucy {
	struct RawTexture {
		lgl::Texture* texture = nullptr;
		std::string name = "New Texture", filename = "";
		uuid id = GetID();

		RawTexture() {}
	};
}