#pragma once

#include <string>
#include <Lucy/UUID.h>
#include <Lucy/ECS.h>

namespace lucy {
	struct Tag {
		uuid id = GetID();
		std::string name = "";
		bool hidden = false;

		Entity parent = (Entity)0;

		Tag(const std::string& name, const uuid& id): name(name), id(id) {}
		Tag(const std::string& name): name(name) {}
		Tag() {}
		~Tag() {}
	};
}