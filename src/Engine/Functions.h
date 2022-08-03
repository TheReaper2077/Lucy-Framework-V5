#pragma once

#include "ECS.h"

namespace lucy {
	struct Functions {
		Entity main_camera = (Entity)0;
		bool enable_debug_render = false;

		void SetCameraEntity(const Entity& entity);
		Entity GetCameraEntity();
		void EnableDebugRender(bool enable);
	};
}