#include "EditorSystem.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <SDL2/SDL.h>
#include <Engine/Window.h>
#include <Editor/EditorStatus.h>
#include <Components/Components.h>

void lucy::System::EditorSystemInitialize(Registry& registry) {
	auto& window = registry.store<Window>();
	auto& editorstatus = registry.store<Editor::EditorStatus>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigDockingWithShift = true;

	ImGui_ImplSDL2_InitForOpenGL(window.sdl_window, (void*)window.sdl_glcontext);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGui::StyleColorsDark();

	auto editor_camera = registry.create();
	auto& camera = registry.emplace<Camera>(editor_camera);

	camera.framebuffer = lgl::MakeFrameBuffer();
}

void EditorLayer() {
	// if (!panel_open) return;

	// auto* window = registry.store<WindowRegistry>()[MAIN_WINDOW];
	// auto* editorwindow = registry.store<WindowRegistry>()[EDITOR_WINDOW];

	// if (editorwindow->framebuffer == nullptr) assert(false);

	// ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	// ImGui::Begin(editorwindow->title.c_str(), &panel_open);
	// ImGui::PopStyleVar();

	// // editorwindow->window_focus = ImGui::IsWindowFocused();
	// // editorwindow->mouse_hover = ImGui::IsWindowHovered();

	// editorwindow->pos.x = ImGui::GetWindowPos().x;
	// editorwindow->pos.y = ImGui::GetWindowPos().y;
	// editorwindow->size.x = ImGui::GetWindowSize().x;
	// editorwindow->size.y = ImGui::GetWindowSize().y;

	// ImGui::GetWindowDrawList()->AddImage((void*)editorwindow->framebuffer->texture->id, ImVec2(editorwindow->pos.x, editorwindow->pos.y), ImVec2(editorwindow->pos.x + editorwindow->size.x, editorwindow->pos.y + editorwindow->size.y), ImVec2(0, (float)editorwindow->size.y / window->size.y), ImVec2((float)editorwindow->size.x / window->size.x, 0));

	// ImGui::End();
}
void GameLayer() {

}

void lucy::System::EditorSystemUpdate(Registry& registry) {
	
}
