#include "Editor.h"
#include <Components/Components.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <Engine/ECS.h>
#include <Engine/Engine.h>
#include <Engine/Window.h>
#include "EditorStatus.h"
#include "ImGuiStyles.h"
#include "PanelRegistry.h"
#include <Registry/Registry.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Editor::Init(SDL_Window* sdl_window, SDL_GLContext* sdl_glcontext) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigDockingWithShift = true;

	ImGui_ImplSDL2_InitForOpenGL(sdl_window, (void*)sdl_glcontext);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGui::StyleColorsDark();
	VS_Theme();

	auto& editorstatus = registry.store<EditorStatus>();
	auto& windowregistry = registry.store<WindowRegistry>();
	auto& panelregistry = registry.store<PanelRegistry>();
	auto* window = registry.store<WindowRegistry>()[MAIN_WINDOW];

	panelregistry.Init();

	{
		auto entity = registry.create();
		auto& tag = registry.emplace<Tag>(entity, "EditorCamera");
		auto& transform = registry.emplace<Transform>(entity);
		auto& camera = registry.emplace<Camera>(entity);

		tag.hidden = true;

		camera.enable = true;
		camera.mode = ViewMode_FPS;
		camera.window_id = EDITOR_WINDOW;

		editorstatus.editor_camera = entity;
	}

	auto* editor_window = windowregistry[EDITOR_WINDOW];
	editor_window->title = "Editor";
	editor_window->framebuffer = lgl::MakeFrameBuffer(window->size.x, window->size.y, true);

	auto* game_window = windowregistry[GAME_WINDOW];
	game_window->title = window->title;
	game_window->framebuffer = lgl::MakeFrameBuffer(window->size.x, window->size.y, false);
}

void lucy::Editor::Render() {
	auto* window = registry.store<WindowRegistry>()[MAIN_WINDOW];
	auto& events = registry.store<Events>();
	auto& editorstatus = registry.store<EditorStatus>();
	auto& panelregistry = registry.store<PanelRegistry>();

	static bool p_open = false, show_demo = false;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(window->size.x, window->size.y));

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
	}

	panelregistry.Render();
	// ImGui::ShowDemoWindow(&show_demo);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
