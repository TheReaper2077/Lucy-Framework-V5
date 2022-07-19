#include "Panel.h"
#include "EditorStatus.h"
#include <Engine/Events.h>
#include <Engine/Functions.h>
#include "Gui.h"
#include <Components/Components.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel<lucy::PanelInstance_SceneHeirarchy>::Render() {
	if (!panel_open) return;

	auto& events = registry.store<Events>();

	if (ImGui::Begin("Scene", &panel_open)) {
		static bool open, toggle;
		auto& selected_entity = registry.store<EditorStatus>().selected_entity;
		
		ImGui::PopupOpenLogic(open, toggle);

		for (auto [entity, tag]: registry.view<Tag>().each()) {
			if (tag.hidden) continue;

			if (ImGui::TreeNodeEx(tag.name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
				if (ImGui::IsItemClicked()) {
					selected_entity = entity;
				}

				if (ImGui::IsItemHovered() && registry.store<Events>().IsButtonPressed(SDL_BUTTON_RIGHT)) {
					ImGui::OpenPopup("Entity SHMenu");
					open = false;
				}

				if (ImGui::BeginPopup("Entity SHMenu")) {
					if (ImGui::Selectable("Delete")) {
						if (selected_entity == entity) {
							selected_entity = (Entity)0;
						}
						registry.destroy(entity);
					}
					ImGui::EndPopup();
				}
				
				ImGui::TreePop();
			}
		}

		if (open) {
			ImGui::OpenPopup("Scene Shortcut");
		}

		if (ImGui::BeginPopup("Scene Shortcut")) {
			auto& functions = registry.store<Functions>();

			if (ImGui::Selectable("New Entity")) {
				selected_entity = functions.CreateEmptyEntity();
			}
			if (ImGui::Selectable("New Camera")) {
				selected_entity = functions.CreateCameraEntity();
			}
			if (ImGui::Selectable("New Sprite")) {
				selected_entity = functions.CreateSpriteEntity();
			}
			if (ImGui::Selectable("New Light")) {
				selected_entity = functions.CreateLightEntity();
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}
