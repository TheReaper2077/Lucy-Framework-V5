#include "InspectorPanel.h"
#include <Structures/Structures.h>
#include <Lucy/Lucy.h>
#include <Editor/EditorState.h>
#include <imgui_lucy_impl.h>

static auto& registry = lucy::Registry::Instance();

namespace lucy {
	template <typename T>
	void InspectorComponent(lucy::Entity entity);
}

template <>
void lucy::InspectorComponent<lucy::Tag>(lucy::Entity entity) {
	auto* tag = registry.try_get<Tag>(entity);

	if (tag != nullptr) {
		if (ImGui::TreeNodeEx("Tag")) {
			ImGui::Text("Name: ");
			ImGui::SameLine();
			ImGui::Text(tag->name.c_str());
			ImGui::Text("ID: ");
			ImGui::SameLine();
			ImGui::Selectable(std::to_string(tag->id).c_str());
			ImGui::TreePop();
		}
	}
}

template <>
void lucy::InspectorComponent<lucy::Transform>(lucy::Entity entity) {
	auto* transform = registry.try_get<Transform>(entity);

	if (transform != nullptr) {
		if (ImGui::TreeNodeEx("Transform")) {
			ImGui::TransformFloat3("Translation", &transform->translation[0]);
			ImGui::TransformFloat3("Rotation", &transform->rotation[0]);
			ImGui::TransformFloat3("Scale", &transform->scale[0]);

			ImGui::TreePop();
		}
	}
}

// template <>
// void lucy::InspectorComponent<lucy::Tag>(lucy::Entity entity) {
// 	auto* tag = registry.try_get<Tag>(entity);

// 	if (tag != nullptr) {
// 		if (ImGui::TreeNodeEx("Tag")) {
// 			ImGui::TreePop();
// 		}
// 	}
// }

// template <>
// void lucy::InspectorComponent<lucy::Tag>(lucy::Entity entity) {
// 	auto* tag = registry.try_get<Tag>(entity);

// 	if (tag != nullptr) {
// 		if (ImGui::TreeNodeEx("Tag")) {
// 			ImGui::TreePop();
// 		}
// 	}
// }

// template <>
// void lucy::InspectorComponent<lucy::Tag>(lucy::Entity entity) {
// 	auto* tag = registry.try_get<Tag>(entity);

// 	if (tag != nullptr) {
// 		if (ImGui::TreeNodeEx("Tag")) {
// 			ImGui::TreePop();
// 		}
// 	}
// }

void lucy::Panel::InspectorPanel() {
	auto& editor_state = registry.store<lucy::EditorState>();

	auto& entity = editor_state.selected_entity;

	if (ImGui::Begin("Inspector")) {
		if (entity != NULL_ENTITY) {
			InspectorComponent<Tag>(entity);
			InspectorComponent<Transform>(entity);
		}

		ImGui::End();
	}
}