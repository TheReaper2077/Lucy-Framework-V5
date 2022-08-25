#pragma once

#include "ECS.h"

namespace lucy {
	namespace Util {
		bool SerializeEntities(const std::string& filename);
		void DeserializeEntities(const std::string& filename);
		
		bool SerializeSpriteRegistry(const std::string& filename);
		void DeserializeSpriteRegistry(const std::string& filename);
	}
}