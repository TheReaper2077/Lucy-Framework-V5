#include "Panel.h"
#include "EditorStatus.h"
#include <Engine/Events.h>
#include "Gui.h"
#include <Components/Components.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel<lucy::PanelInstance_SceneHeirarchy>::Render() {
	if (!panel_open) return;

	auto& events = registry.store<Events>();

	if (ImGui::Begin("Scene", &panel_open)) {
		static bool open, toggle;
		// std::unordered_map<Entity, Node> scene_tree;
		auto& selected_entity = registry.store<EditorStatus>().selected_entity;
		
		ImGui::PopupOpenLogic(open, toggle);

		for (auto [entity, tag]: registry.view<Tag>().each()) {
			if (tag.hidden) continue;

			// auto parent = registry.try_get<ParentEntity>(entity);

			// if (scene_tree.find(entity) == scene_tree.end())
			// 	scene_tree[entity] = Node{};

			// if (parent != nullptr) {
			// 	scene_tree[entity].parent = *parent;

			// 	if (scene_tree.find(*parent) == scene_tree.end())
			// 		scene_tree[*parent] = Node{};

			// 	scene_tree[*parent].children.push_back(entity);
			// }

			if (ImGui::TreeNodeEx(tag.name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
				if (ImGui::IsItemClicked()) {
					selected_entity = entity;
				}

				if (ImGui::IsItemHovered() && registry.store<Events>().IsButtonPressed(SDL_BUTTON_RIGHT)) {
					// registry.store<Events>().mouse_pressed.c
					ImGui::OpenPopup("Entity SHMenu");
					open = false;
				}

				// if (ImGui::BeginPopup("Entity SHMenu")) {
				// 	auto& functions = registry.store<Functions>();

				// 	if (ImGui::Selectable("Delete")) {
				// 		if (selected_entity == entity) {
				// 			selected_entity = (Entity)0;
				// 		}
				// 		registry.destroy(entity);
				// 	}
				// 	ImGui::EndPopup();
				// }
				
				ImGui::TreePop();
			}
		}

		if (open) {
			ImGui::OpenPopup("Scene Shortcut");
		}

		// for (auto& pair: scene_tree) {
		// 	if ((uint32_t)pair.second.parent == 0)
		// 		RenderTree(pair.first, registry, scene_tree, scene_tree[pair.first]);
		// }

		if (ImGui::BeginPopup("Scene Shortcut")) {
			// auto& functions = registry.store<Functions>();

			// if (ImGui::Selectable("New Entity")) {
			// 	selected_entity = functions.CreateEmptyEntity();
			// }
			// if (ImGui::Selectable("New Camera")) {
			// 	selected_entity = functions.CreateCameraEntity();
			// }
			// if (ImGui::Selectable("New Sprite")) {
			// 	selected_entity = functions.CreateSpriteEntity();
			// }
			// if (ImGui::Selectable("New Light")) {
			// 	selected_entity = functions.CreateLightEntity();
			// }
			// ImGui::EndPopup();
		}
	}
	ImGui::End();
}
