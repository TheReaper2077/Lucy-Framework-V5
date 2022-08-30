#include "GamePanel.h"
#include <Lucy/Lucy.h>
#include <imgui_lucy_impl.h>
#include <Editor/EditorState.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel::GamePanel() {
	auto& engine_state = registry.store<lucy::State>();
	auto& window = registry.store<lucy::Window>();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });

	ImGui::Begin(window.title.c_str());
	ImGui::PopStyleVar();

	if (engine_state.camera_entity == NULL_ENTITY)
		return;

	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();

	auto& camera = registry.get<Camera>(engine_state.camera_entity);

	window.pos.x = pos.x;
	window.pos.y = pos.y;
	window.size.x = size.x;
	window.size.y = size.y;

	if (camera.framebuffer != nullptr)
		ImGui::GetWindowDrawList()->AddImage((void*)camera.framebuffer->texture->id, { pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, { 0, window.size.y / camera.framebuffer->height }, { window.size.x / camera.framebuffer->width, 0 });

	ImGui::End();
}