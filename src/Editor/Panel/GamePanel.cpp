#include "GamePanel.h"
#include <Lucy/Lucy.h>
#include <imgui_lucy_impl.h>
#include <Editor/EditorState.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel::GamePanel() {
	auto& editor_state = registry.store<lucy::EditorState>();
	auto& window = registry.store<lucy::Window>();

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