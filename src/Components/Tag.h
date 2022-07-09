#pragma once

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>
#include <string>

namespace lucy::Components {
	struct Tag {
		std::string name = "";
		std::string id = uuids::to_string(uuids::uuid_system_generator{}());

		Tag(const std::string& name, const std::string& id): name(name), id(id) {}
		Tag(const std::string& name): name(name) {}
	};
}