#include "EditorSystem.h"
#include <imgui.h>
#include <imgui_lucy_impl.h>
#include <SDL2/SDL.h>
#include <Engine/Window.h>
#include <Engine/Events.h>
#include <Engine/Functions.h>
#include <Editor/EditorStatus.h>
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
					ImGui::ColorPicker4("Clear Color", &camera->clear_color[0]);

					ImGui::TreePop();
				}
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
		if (events.IsWindowResized())
			mainwindow.size = events.GetWindowSize();
		if (events.IsWindowMoved())
			mainwindow.pos = events.GetWindowPosition();
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
	// Panel::EditorLayer(registry);

	static bool show_demo = false;
	if (events.IsKeyPressed(SDL_SCANCODE_F12))
		show_demo = !show_demo;

	if (show_demo)
		ImGui::ShowDemoWindow(&show_demo);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();

	window.SetCurrent();
}
