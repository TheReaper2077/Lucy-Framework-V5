#pragma once

#include <Engine/ECS.h>

namespace lucy::System {
	namespace Panel {
		void GameLayer(Registry& registry);
		void EditorLayer(Registry& registry);
		void HeirarchyLayer(Registry& registry);
		void InspectorLayer(Registry& registry);
		void EngineManagerLayer(Registry& registry);
		void MaterialRegistryLayer(Registry& registry);
		void MeshRegistryLayer(Registry& registry);
	}

	void EditorSystemUpdate(Registry& registry);
}