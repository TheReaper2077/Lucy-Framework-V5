#pragma once

#include <string>
#include <LucyUtil/LucyUtil.h>
#include <Lucy/ECS.h>

namespace lucy {
	struct Tag {
		LUTIL_UUID id = LUTIL_GENERATE_UUID;
		std::string name = "";
		bool hidden = false;

		Entity parent = (Entity)0;

		Tag(const std::string& name, const LUTIL_UUID& id): name(name), id(id) {}
		Tag(const std::string& name): name(name) {}
		Tag() {}
		~Tag() {}
	};
}