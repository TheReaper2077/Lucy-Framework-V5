#pragma once

#include "ECS.h"

namespace lucy {
	struct State {
		bool is_entity_selected;
		bool allow_entity_selection;

		Entity selected_entity = (Entity)0;
	};
}