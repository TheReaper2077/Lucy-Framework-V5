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

void lucy::System::EditorSystemInitialize(Registry& registry) {
	auto& window = registry.store<Window>();
	auto& mainwindow = registry.store<Editor::MainWindow>();
	auto& editorstatus = registry.store<Editor::EditorStatus>();
	auto& events = registry.store<Events>();
	auto& functions = registry.store<Functions>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigDockingWithShift = true;

	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;

	ImGui_ImplSDL2_InitForOpenGL(window.sdl_window, (void*)window.sdl_glcontext);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGui::StyleColorsDark();

	functions.render_target_to_screen = true;

	events.AddFunction([](SDL_Event& event) {
		ImGui_ImplSDL2_ProcessEvent(&event);
	});
}

void lucy::System::Panel::GameLayer(lucy::Registry& registry) {
	auto& window = registry.store<Window>();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	static bool panel_open;
	ImGui::Begin(window.title.c_str(), &panel_open);
	ImGui::PopStyleVar();

	// window.window_focus = ImGui::IsWindowFocused();
	// window.mouse_hover = ImGui::IsWindowHovered();

	window.pos.x = ImGui::GetWindowPos().x;
	window.pos.y = ImGui::GetWindowPos().y;
	window.size.x = ImGui::GetWindowSize().x;
	window.size.y = ImGui::GetWindowSize().y;

	if (window.framebuffer != nullptr)
		if (window.framebuffer->width == window.size.x && window.framebuffer->height == window.size.y)
			ImGui::GetWindowDrawList()->AddImage((void*)window.framebuffer->texture->id, ImVec2(window.pos.x, window.pos.y), ImVec2(window.pos.x + window.size.x, window.pos.y + window.size.y), ImVec2(0, (float)window.size.y / window.size.y), ImVec2((float)window.size.x / window.size.x, 0));

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
	auto& mainwindow = registry.store<Editor::MainWindow>();
	
	static bool toggle = false;
	if (!functions.render_target_to_screen && !toggle) {
		mainwindow.size = window.size;
		mainwindow.title = window.title;
		toggle = true;
	} else if (functions.render_target_to_screen && toggle) {
		window.ResetPosition();
		window.ResetSize();
		toggle = false;
	}

	if (!functions.render_target_to_screen) {
		// window.Hide();

		if (events.IsWindowResized())
			mainwindow.size = events.GetWindowSize();
		if (events.IsWindowMoved())
			mainwindow.pos = events.GetWindowPosition();
	} else {
		// window.Show();
	}

	if (events.IsKeyChord({ SDL_SCANCODE_LALT, SDL_SCANCODE_F4 })) {
		events.IsQuittable() = true;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (!functions.render_target_to_screen) {
		static bool p_open = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::SetNextWindowPos(ImVec2(mainwindow.pos.x, mainwindow.pos.y));
		ImGui::SetNextWindowSize(ImVec2(mainwindow.size.x, mainwindow.size.y));

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace", &p_open, window_flags);

		ImGui::PopStyleVar(3);
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		ImGui::End();

		Panel::GameLayer(registry);
	}

	Panel::HeirarchyLayer(registry);
	Panel::InspectorLayer(registry);
	Panel::EngineManagerLayer(registry);
	Panel::MaterialRegistryLayer(registry);

	static bool show_demo = false;
	if (events.IsKeyPressed(SDL_SCANCODE_F12) && !show_demo)
		show_demo = true;
	if (events.IsKeyPressed(SDL_SCANCODE_F11) && show_demo)
		show_demo = false;

	if (show_demo)
		ImGui::ShowDemoWindow(&show_demo);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();

	window.SetCurrent();
}
