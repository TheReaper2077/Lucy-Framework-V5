#include "InspectorPanel.h"
#include <Structures/Structures.h>
#include <Lucy/Lucy.h>
#include <Editor/EditorState.h>
#include <imgui_lucy_impl.h>

static auto& registry = lucy::Registry::Instance();
static uint32_t flags = ImGuiTreeNodeFlags_DefaultOpen;

namespace lucy {
	template <typename T>
	void InspectorComponent(lucy::Entity entity);
}

template <>
void lucy::InspectorComponent<lucy::Tag>(lucy::Entity entity) {
	auto* tag = registry.try_get<Tag>(entity);

	if (tag != nullptr) {
		if (ImGui::TreeNodeEx("Tag", flags)) {
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
		if (ImGui::TreeNodeEx("Transform", flags)) {
			ImGui::TransformFloat3("Translation", &transform->translation[0]);
			ImGui::TransformFloat3("Rotation", &transform->rotation[0]);
			ImGui::TransformFloat3("Scale", &transform->scale[0]);

			ImGui::TreePop();
		}
	}
}

template <>
void lucy::InspectorComponent<lucy::Light>(lucy::Entity entity) {
	auto* light = registry.try_get<Light>(entity);

	if (light != nullptr) {
		if (ImGui::TreeNodeEx("Light", flags)) {
			ImGui::EnumComboLogic("Mode", { "DIRECTIONAL_LIGHT", "POINT_LIGHT", "AREAL_LIGHT", "SPOT_LIGHT" }, light->mode, { "AREAL_LIGHT", "SPOT_LIGHT" });
			ImGui::ColorEdit4("Color", &light->color[0], ImGuiColorEditFlags_NoInputs);
			ImGui::SliderFloat("Ambient", &light->ambient, 0, 1);
			ImGui::SliderFloat("Diffuse", &light->diffuse, 0, 1);
			ImGui::SliderFloat("Specular", &light->specular, 0, 1);

			ImGui::TreePop();
		}
	}
}

template <>
void lucy::InspectorComponent<lucy::MeshRenderer>(lucy::Entity entity) {
	auto* meshrenderer = registry.try_get<MeshRenderer>(entity);

	if (meshrenderer != nullptr) {
		if (ImGui::TreeNodeEx("MeshRenderer", flags)) {
			if (meshrenderer->material != nullptr) {
				if (ImGui::TreeNodeEx("Material", flags)) {
					ImGui::SliderFloat3("Ambient", &meshrenderer->material->ambient[0], 0, 1);
					ImGui::SliderFloat3("Diffuse", &meshrenderer->material->diffuse[0], 0, 1);
					ImGui::SliderFloat3("Specular", &meshrenderer->material->specular[0], 0, 1);
					ImGui::SliderFloat("Shininess", &meshrenderer->material->shininess, 0, 128);

					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}
	}
}

// template <>
// void lucy::InspectorComponent<lucy::Tag>(lucy::Entity entity) {
// 	auto* tag = registry.try_get<Tag>(entity);

// 	if (tag != nullptr) {
// 		if (ImGui::TreeNodeEx("Tag", flags)) {
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
			InspectorComponent<Light>(entity);
			InspectorComponent<MeshRenderer>(entity);
		}

		ImGui::End();
	}
}