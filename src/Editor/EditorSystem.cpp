#include <Lucy/Lucy.h>
#include "EditorSystem.h"
#include "EditorCamera.h"
#include "EditorState.h"

static auto& registry = lucy::Registry::Instance();
static auto& window = registry.store<lucy::Window>();
static auto& editor_state = registry.store<lucy::EditorState>();
static auto& engine_state = registry.store<lucy::State>();

namespace lucy {
	void EditorPanel() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });

		ImGui::Begin("Editor");
		ImGui::PopStyleVar();

		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		auto& camera = registry.get<Camera>(editor_state.camera_entity);

		if (camera.width != size.x || camera.height != size.y && camera.framebuffer != nullptr) {
			delete camera.framebuffer;
			camera.framebuffer = nullptr;
		}

		camera.width = size.x;
		camera.height = size.y;

		if (camera.framebuffer == nullptr) {
			camera.framebuffer = new lgl::FrameBuffer(camera.width, camera.height, true);
		}

		ImGui::GetWindowDrawList()->AddImage((void*)camera.framebuffer->texture->id, { pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, { 0, 1 }, { 1, 0 });

		ImGui::End();
	}

	void GamePanel() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });

		ImGui::Begin(window.title.c_str());
		ImGui::PopStyleVar();

		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		auto& camera = registry.get<Camera>(editor_state.camera_entity);

		if (camera.width != size.x || camera.height != size.y && camera.framebuffer != nullptr) {
			delete camera.framebuffer;
			camera.framebuffer = nullptr;
		}

		camera.width = size.x;
		camera.height = size.y;

		if (camera.framebuffer == nullptr) {
			camera.framebuffer = new lgl::FrameBuffer(camera.width, camera.height, true);
		}

		ImGui::GetWindowDrawList()->AddImage((void*)camera.framebuffer->texture->id, { pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, { 0, 1 }, { 1, 0 });

		ImGui::End();
	}

	void InspectorPanel() {

	}
}

void lucy::System::EditorSystem() {
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
		camera.position = { 0, 0, 10 };
		camera.update = EditorCameraUpdate;
	}

	// GamePanel();
	EditorPanel();
	InspectorPanel();
}
