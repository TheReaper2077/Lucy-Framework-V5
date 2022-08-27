#pragma once

#include <Lucy/Lucy.h>

namespace lucy {
	struct EditorState {
		Entity camera_entity = (Entity)0;

		bool enable_viewports = false;
	};
}