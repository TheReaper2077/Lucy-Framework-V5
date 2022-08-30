#pragma once

#include <imgui_lucy_impl.h>

namespace lucy::Panel {
	template <typename T>
	void InspectorComponent(Entity entity);

	void EditorPanel();
	void GamePanel();
	void InspectorPanel();
	void HeirarchyPanel();
}

namespace lucy::System {
	void EditorSystem();
}