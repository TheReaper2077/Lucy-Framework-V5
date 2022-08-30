#include "HeirarchyPanel.h"
#include <Lucy/Lucy.h>
#include <imgui_lucy_impl.h>
#include <Editor/EditorState.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel::HeirarchyPanel() {
	auto& editor_state = registry.store<lucy::EditorState>();

	if (ImGui::Begin("Heirarchy")) {
		for (auto [entity, tag]: registry.view<Tag>().each()) {
			if (ImGui::TreeNodeEx(tag.name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
				ImGui::TreePop();
			}

			if (ImGui::IsItemClicked()) {
				editor_state.selected_entity = entity;
			}
		}

		ImGui::End();
	}
}