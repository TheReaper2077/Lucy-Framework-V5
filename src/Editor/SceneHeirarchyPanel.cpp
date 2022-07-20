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
	auto& editorstatus = registry.store<EditorStatus>();

	if (ImGui::Begin("Scene", &panel_open)) {
		static bool open, toggle;
		
		ImGui::PopupOpenLogic(open, toggle);

		for (auto [entity, tag]: registry.view<Tag>().each()) {
			if (tag.hidden) continue;

			if (ImGui::TreeNodeEx(tag.name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
				if (ImGui::IsItemClicked()) {
					editorstatus.SetEntity(entity);
				}

				if (ImGui::IsItemHovered() && registry.store<Events>().IsButtonPressed(SDL_BUTTON_RIGHT)) {
					ImGui::OpenPopup("Entity SHMenu");
					open = false;
				}

				if (ImGui::BeginPopup("Entity SHMenu")) {
					if (ImGui::Selectable("Delete")) {
						if (editorstatus.GetEntityID() == entity) {
							editorstatus.SetEntity((Entity)0);
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
				editorstatus.SetEntity(functions.CreateEmptyEntity());
			}
			if (ImGui::Selectable("New Camera")) {
				editorstatus.SetEntity(functions.CreateCameraEntity());
			}
			if (ImGui::Selectable("New Sprite")) {
				editorstatus.SetEntity(functions.CreateSpriteEntity());
			}
			if (ImGui::Selectable("New Light")) {
				editorstatus.SetEntity(functions.CreateLightEntity());
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}
