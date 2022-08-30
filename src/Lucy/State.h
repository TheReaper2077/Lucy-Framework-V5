#pragma once

#include "ECS.h"

namespace lucy {
	struct State {
		Entity camera_entity = (Entity)0;

		bool render_to_screen = true;

		uint32_t fps, ups;
		
	};
}