#include "EditorPanel.h"
#include <Lucy/Lucy.h>
#include <iostream>
#include <imgui_lucy_impl.h>
#include <Editor/EditorState.h>
#include <glm/gtx/string_cast.hpp>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel::EditorPanel() {
	auto& editor_state = registry.store<lucy::EditorState>();
	auto& window = registry.store<lucy::Window>();

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

	camera.posx = pos.x;
	camera.posy = pos.y;
	camera.width = size.x;
	camera.height = size.y;

	if (camera.framebuffer == nullptr) {
		camera.framebuffer = new lgl::FrameBuffer(camera.width, camera.height, true);
	}

	ImGui::GetWindowDrawList()->AddImage((void*)camera.framebuffer->texture->id, { pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, { 0, 1 }, { 1, 0 });

	if (editor_state.selected_entity != NULL_ENTITY) {
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);

		auto* transform = registry.try_get<Transform>(editor_state.selected_entity);
		if (transform != nullptr) {
			glm::mat4 model = transform->GetModelMatrix();
			glm::mat4 delta;

			float snap = 0;
			ImGuizmo::Manipulate(&camera.view[0][0], &camera.projection[0][0], ImGuizmo::OPERATION::ROTATE | ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, &model[0][0], &delta[0][0], &snap);

			if (ImGuizmo::IsUsing()) {
				glm::vec3 translation, rotation, scale;

				ImGuizmo::DecomposeMatrixToComponents(&model[0][0], &translation[0], &rotation[0], &scale[0]);

				transform->translation = translation;
				transform->rotation += (rotation - transform->rotation);
				transform->scale = scale;
			}
		}
	}

	ImGui::End();
}
