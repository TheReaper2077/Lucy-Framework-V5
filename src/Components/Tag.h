#pragma once

#include <string>
#include <Engine/UUID.h>

namespace lucy {
	struct Tag {
		uuid id = GetID();
		std::string name = "";
		bool hidden = false;

		Tag(const std::string& name, const uuid& id): name(name), id(id) {}
		Tag(const std::string& name): name(name) {}
	};
}