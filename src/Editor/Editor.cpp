#include "Editor.h"
#include "EditorState.h"
#include <Lucy/Lucy.h>

static auto& registry = lucy::Registry::Instance();
static auto& engine_state = registry.store<lucy::State>();
static auto& editor_state = registry.store<lucy::EditorState>();

void lucy::Editor::Initialize() {
	engine_state.render_to_screen = false;

	editor_state.enable_viewports = true;

	auto& window = registry.store<Window>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigDockingWithShift = true;

	if (editor_state.enable_viewports) {
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	}

	ImGui_ImplSDL2_InitForOpenGL(window.sdl_window, (void*)window.sdl_glcontext);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGui::StyleColorsDark();

	Events::AddFunction([](SDL_Event& event) {
		ImGui_ImplSDL2_ProcessEvent(&event);
	});
}

void lucy::Editor::RenderBegin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	auto& window = registry.store<Window>();

	// Screen
	{
		static bool p_open = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoTitleBar;
		
		int x = 0, y = 0, w = 0, h = 0;
		SDL_GetWindowSize(window.sdl_window, &w, &h);

		if (editor_state.enable_viewports)
			SDL_GetWindowPosition(window.sdl_window, &x, &y);

		ImGui::SetNextWindowPos(ImVec2(x, y));
		ImGui::SetNextWindowSize(ImVec2(w, h));

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });

		ImGui::Begin("DockSpace", &p_open, window_flags);

		ImGui::PopStyleVar(3);
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		ImGui::End();
	}
}

void lucy::Editor::RenderEnd() {
	auto& window = registry.store<Window>();
	auto& events = registry.store<Events>();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	if (editor_state.enable_viewports) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		window.SetCurrent();
	}
}

void lucy::Editor::AddLayer(system_func func) {
	for (auto fn: self->systems_array)
		assert(func != fn);

	self->systems_array.push_back(func);
}

void lucy::Editor::Update() {
	RenderBegin();

	for (auto system_func: self->systems_array) {
		system_func();
	}

	RenderEnd();
}

void lucy::Editor::ShutDown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
}
