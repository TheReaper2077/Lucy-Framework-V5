#include <Lucy/Lucy.h>
#include <Editor/Panel/Panel.h>
#include "EditorSystem.h"
#include "EditorCamera.h"
#include "EditorState.h"

static auto& registry = lucy::Registry::Instance();

void lucy::System::EditorSystem() {
	auto& editor_state = registry.store<lucy::EditorState>();
	auto& engine_state = registry.store<lucy::State>();
	
	engine_state.render_to_screen = false;

	if (editor_state.camera_entity == (Entity)0) {
		editor_state.camera_entity = registry.create();

		auto& tag = registry.emplace<Tag>(editor_state.camera_entity);
		auto& transform = registry.emplace<Transform>(editor_state.camera_entity);
		auto& camera = registry.emplace<Camera>(editor_state.camera_entity);

		tag.name = "Editor Camera";
		tag.hidden = true;

		camera.enable = true;
		camera.clear_color = { 0, 0, 0, 1 };
		camera.position = { 0, 0, 50 };
		camera.update = EditorCameraUpdate;
	}

	Panel::GamePanel();
	Panel::HeirarchyPanel();
	Panel::InspectorPanel();
	Panel::StatusPanel();
	Panel::EditorPanel();
}
