#pragma once

#include <Engine/ECS.h>
#include <string>

namespace lucy {
	struct EditorStatus {
		Entity selected_entity = (Entity)0;
		Entity editor_camera = (Entity)0;

		std::string selected_texture = "";
	};
}