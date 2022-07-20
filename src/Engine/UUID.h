#pragma once

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>

namespace lucy {
	typedef std::string uuid;

	static const uuid GetID() {
		return uuids::to_string(uuids::uuid_system_generator{}());
	}
}