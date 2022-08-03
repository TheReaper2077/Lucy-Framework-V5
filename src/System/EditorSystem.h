#pragma once

#include <Engine/ECS.h>

namespace lucy::System {
	void EditorSystemUpdate(Registry& registry);
	void EditorSystemInitialize(Registry& registry);
}