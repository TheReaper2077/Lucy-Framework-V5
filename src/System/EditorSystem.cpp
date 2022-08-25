#include "EditorSystem.h"
#include <imgui.h>
#include <iostream>
#include <imgui_lucy_impl.h>
#include <SDL2/SDL.h>
#include <Engine/Window.h>
#include <Engine/Events.h>
#include <Engine/Functions.h>
#include <Editor/EditorStatus.h>
#include <Registry/Registry.h>
#include <Components/Components.h>

void lucy::System::Panel::GameLayer(lucy::Registry& registry) {
	auto& gamewindow = registry.store<GameWindow>();
	auto& window = registry.store<Window>();
	auto& functions = registry.store<Functions>();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	static bool panel_open;
	ImGui::Begin(gamewindow.title.c_str(), &panel_open);
	ImGui::PopStyleVar();

	// gamewindow.window_focus = ImGui::IsWindowFocused();
	// gamewindow.mouse_hover = ImGui::IsWindowHovered();

	gamewindow.pos.x = ImGui::GetWindowPos().x;
	gamewindow.pos.y = ImGui::GetWindowPos().y;
	gamewindow.size.x = ImGui::GetWindowSize().x;
	gamewindow.size.y = ImGui::GetWindowSize().y;

	if (gamewindow.framebuffer != nullptr)
		if (gamewindow.framebuffer->width == gamewindow.size.x && gamewindow.framebuffer->height == gamewindow.size.y)
			ImGui::GetWindowDrawList()->AddImage((void*)gamewindow.framebuffer->texture->id, ImVec2(gamewindow.pos.x, gamewindow.pos.y), ImVec2(gamewindow.pos.x + gamewindow.size.x, gamewindow.pos.y + gamewindow.size.y), ImVec2(0, (float)gamewindow.size.y / window.size.y), ImVec2((float)gamewindow.size.x / window.size.x, 0));

	ImGui::End();
}

void lucy::System::Panel::HeirarchyLayer(Registry& registry) {
	auto& editor = registry.store<Editor::EditorStatus>();

	static bool panel_open;
	if (ImGui::Begin("Heirarchy", &panel_open)) {
		for (auto [entity, tag]: registry.view<Tag>().each()) {
			if (ImGui::TreeNodeEx(tag.name.c_str())) {
				editor.selected_entity = entity;

				ImGui::TreePop();
			}

			// if (ImGui::IsItemHovered()) {
			// 	ImGui::OpenPopup("Tag - Info");
			// }

			// if (ImGui::BeginPopup("Tag - Info")) {
			// 	ImGui::Text("ID: ");
			// 	ImGui::SameLine();
			// 	ImGui::Text(tag.id.c_str());

			// 	ImGui::EndPopup();
			// }
		}
	}
	ImGui::End();
}

void lucy::System::Panel::InspectorLayer(Registry& registry) {
	auto& editor = registry.store<Editor::EditorStatus>();
	auto& materialregistry = registry.store<MaterialRegistry>();

	static auto selected_entity = (Entity)0;
	static lgl::Texture* selected_texture = nullptr;

	static bool panel_open;
	if (ImGui::Begin("Inspector", &panel_open)) {
		if (selected_entity != editor.selected_entity) {
			selected_entity = editor.selected_entity;
		}
		// if (selected_texture != editor.selected_texture) {
		// 	selected_entity = (Entity)0;
		// }

		if (selected_entity != (Entity)0) {
			auto* tag = registry.try_get<Tag>(selected_entity);
			if (tag != nullptr) {
				if (ImGui::TreeNodeEx("Tag")) {
					ImGui::Text("ID", tag->id);

					ImGui::SanitisedInputText("Name", tag->name);

					ImGui::TreePop();
				}
			}

			auto* transform = registry.try_get<Transform>(selected_entity);
			if (transform != nullptr) {
				if (ImGui::TreeNodeEx("Transform")) {
					ImGui::TransformFloat3("Translation", &transform->translation[0]);
					ImGui::TransformFloat3("Rotation", &transform->rotation[0]);
					ImGui::TransformFloat3("Scale", &transform->scale[0]);

					ImGui::TreePop();
				}
			}

			auto* camera = registry.try_get<Camera>(selected_entity);
			if (camera != nullptr) {
				if (ImGui::TreeNodeEx("Camera")) {
					ImGui::Checkbox("Enable", &camera->enable);
					ImGui::ColorEdit4("Clear Color", &camera->clear_color[0]);

					if (ImGui::TreeNodeEx("Clear Buffer")) {
						bool color = ((camera->clear_flags & lgl::COLOR_BUFFER_BIT) != 0);
						bool depth = ((camera->clear_flags & lgl::DEPTH_BUFFER_BIT) != 0);
						bool stencil = ((camera->clear_flags & lgl::STENCIL_BUFFER_BIT) != 0);

						ImGui::Checkbox("Color", &color);
						ImGui::Checkbox("Depth", &depth);
						ImGui::Checkbox("Stencil", &stencil);

						if (color)
							camera->clear_flags |= lgl::COLOR_BUFFER_BIT;
						else
							camera->clear_flags &= ~lgl::COLOR_BUFFER_BIT;
						if (depth)
							camera->clear_flags |= lgl::DEPTH_BUFFER_BIT;
						else
							camera->clear_flags &= ~lgl::DEPTH_BUFFER_BIT;
						if (stencil)
							camera->clear_flags |= lgl::STENCIL_BUFFER_BIT;
						else
							camera->clear_flags &= ~lgl::STENCIL_BUFFER_BIT;

						ImGui::TreePop();
					}

					ImGui::DragFloat("Near", &camera->c_near);
					ImGui::DragFloat("Far", &camera->c_far);
					ImGui::DragFloat("Sensitivity", &camera->sensitivity);
					ImGui::DragFloat("Fov", &camera->fov);

					ImGui::TreePop();
				}
			}

			auto* light = registry.try_get<Light>(selected_entity);
			if (light != nullptr) {
				if (ImGui::TreeNodeEx("Light")) {
					ImGui::Checkbox("Enable", &light->enable);
					ImGui::ColorEdit4("Color", &light->color[0]);
					ImGui::EnumComboLogic("Mode", {
						"DIRECTIONAL_LIGHT",
						"AREAL_LIGHT",
						"POINT_LIGHT",
						"SPOT_LIGHT",
					}, light->mode, {
						"POINT_LIGHT",
						"SPOT_LIGHT",
					});

					ImGui::TreePop();
				}
			}

			auto* spriterenderer = registry.try_get<SpriteRenderer>(selected_entity);
			if (spriterenderer != nullptr) {
				if (ImGui::TreeNodeEx("SpriteRenderer")) {
					

					ImGui::TreePop();
				}
			}

			auto* meshrenderer = registry.try_get<MeshRenderer>(selected_entity);
			if (meshrenderer != nullptr) {
				if (ImGui::TreeNodeEx("MeshRenderer")) {
					ImGui::Checkbox("Visible", &meshrenderer->visible);
					ImGui::Checkbox("Lighting", &meshrenderer->enable_lighting);

					if (ImGui::Selectable("Material")) {
						ImGui::OpenPopup("mat_select");
					}

					if (ImGui::BeginPopup("mat_select")) {
						for (auto& pair: materialregistry.material_registry) {
							if (ImGui::Selectable(pair.second.name.c_str())) {
								meshrenderer->material = &pair.second;
							}
						}

						ImGui::EndPopup();
					}

					// if (ImGui::BeginPopup("mesh_select")) {
					// 	for (auto& pair: meshregistry.mesh_registry) {
					// 		if (ImGui::Selectable(pair.second.name.c_str())) {
					// 			meshrenderer.mesh = &pair.second.mesh;
					// 		}
					// 	}

					// 	ImGui::EndPopup();
					// }

					ImGui::TreePop();
				}
			}
		}
	}
	ImGui::End();
}

void lucy::System::Panel::EngineManagerLayer(Registry& registry) {
	auto& functions = registry.store<Functions>();

	static bool panel_open;
	if (ImGui::Begin("PhysicsManger", &panel_open)) {
		if (ImGui::TreeNodeEx("Physics")) {
			ImGui::Checkbox("Enable Physics Caching", &functions.enable_physics_caching);
			ImGui::Checkbox("Enable Physics Render", &functions.enable_physics_object_render);

			ImGui::Text("Current State: ");
			ImGui::SameLine();

			if (functions.IsPhysicsPaused()) {
				ImGui::TextColored({ 0, 0, 1, 1 }, "PAUSED");
			} else if (functions.IsPhysicsStopped()) {
				ImGui::TextColored({ 1, 0, 0, 1 }, "STOPPED");
			} else if (functions.IsPhysicsPlaying()) {
				ImGui::TextColored({ 0, 1, 0, 1 }, "PLAYING");
			}

			if (ImGui::Button("PLAY") && !functions.IsPhysicsPlaying()) {
				functions.PlayPhysics();
			}
			if (ImGui::Button("PAUSE") && !functions.IsPhysicsPaused()) {
				functions.PausePhysics();
			}
			if (ImGui::Button("STOP") && !functions.IsPhysicsStopped()) {
				functions.StopPhysics();
			}

			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Render")) {
			ImGui::InputFloat2("Render Resolution", &functions.render_resolution[0]);

			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void lucy::System::Panel::MaterialRegistryLayer(Registry& registry) {
	auto& materialregistry = registry.store<MaterialRegistry>();

	static bool panel_open;
	if (ImGui::Begin("MaterialRegistry", &panel_open)) {
		for (auto& pair: materialregistry.material_registry) {
			auto& material = pair.second;

			if (ImGui::TreeNode(pair.second.name.c_str())) {
				ImGui::DragFloat3("albedo", &material.albedo[0], 0.01, 0, 1);
				ImGui::DragFloat3("diffuse", &material.diffuse[0], 0.01, 0, 1);
				ImGui::DragFloat3("ambient", &material.ambient[0], 0.01, 0, 1);
				ImGui::DragFloat3("specular", &material.specular[0], 0.01, 0, 1);

				ImGui::DragFloat("roughness", &material.roughness, 0.01, 0, 1);
				ImGui::DragFloat("metallic", &material.metallic, 0.01, 0, 1);
				ImGui::DragFloat("shininess", &material.shininess, 0.01, 0, 1);

				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}

void lucy::System::EditorSystemUpdate(Registry& registry) {
	auto& editor = registry.store<Editor::EditorStatus>();
	auto& window = registry.store<Window>();
	auto& events = registry.store<Events>();
	auto& functions = registry.store<Functions>();

	static bool show_demo = false;
	if (events.IsKeyPressed(SDL_SCANCODE_F12) && !show_demo)
		show_demo = true;
	if (events.IsKeyPressed(SDL_SCANCODE_F11) && show_demo)
		show_demo = false;

	if (show_demo)
		ImGui::ShowDemoWindow(&show_demo);

	if (events.IsKeyChord({ SDL_SCANCODE_LALT, SDL_SCANCODE_F4 }))
		events.IsQuittable() = true;

	Panel::GameLayer(registry);
	Panel::HeirarchyLayer(registry);
	Panel::InspectorLayer(registry);
	Panel::EngineManagerLayer(registry);
	Panel::MaterialRegistryLayer(registry);
}
