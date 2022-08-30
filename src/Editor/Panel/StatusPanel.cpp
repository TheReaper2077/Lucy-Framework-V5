#include "StatusPanel.h"
#include <Structures/Structures.h>
#include <Lucy/Lucy.h>
#include <Editor/EditorState.h>
#include <imgui_lucy_impl.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel::StatusPanel() {
	auto& engine_state = registry.store<State>();

	if (ImGui::Begin("Status")) {
		ImGui::Text("FPS: ");
		ImGui::SameLine();
		ImGui::Text(std::to_string(engine_state.fps).c_str());

		ImGui::End();
	}
}

