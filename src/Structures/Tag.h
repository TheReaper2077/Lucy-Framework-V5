#pragma once

#include <string>
#include <LucyUtil/LucyUtil.h>
#include <Lucy/ECS.h>

namespace lucy {
	struct Tag {
		UTIL_UUID id = UTIL_GENERATE_UUID;
		std::string name = "";
		bool hidden = false;

		Entity parent = (Entity)0;

		Tag(const std::string& name, const UTIL_UUID& id): name(name), id(id) {}
		Tag(const std::string& name): name(name) {}
		Tag() {}
		~Tag() {}
	};
}