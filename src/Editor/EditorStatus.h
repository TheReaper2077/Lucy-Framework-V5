#pragma once

#include <Engine/ECS.h>

namespace lucy {
	struct EditorStatus {
		Entity selected_entity = (Entity)0;
		Entity editor_camera = (Entity)0;
	};
}