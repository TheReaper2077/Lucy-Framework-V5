#pragma once

#include <Structures/Structures.h>

namespace lucy {
	struct MaterialRegistry {
		void Init();
		Material* operator[](const std::string& id) {
			
		}
	};
}