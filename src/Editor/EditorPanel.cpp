// #include "Panel.h"
// #include <Engine/ECS.h>
// #include <imgui.h>
// #include <imgui_internal.h>
// #include <Registry/Registry.h>

// static auto& registry = lucy::Registry::Instance();

// void lucy::Panel<lucy::PanelInstance_Editor>::Render() {
// 	if (!panel_open) return;

// 	auto* window = registry.store<WindowRegistry>()[MAIN_WINDOW];
// 	auto* editorwindow = registry.store<WindowRegistry>()[EDITOR_WINDOW];

// 	if (editorwindow->framebuffer == nullptr) assert(false);

// 	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

// 	ImGui::Begin(editorwindow->title.c_str(), &panel_open);
// 	ImGui::PopStyleVar();

// 	// editorwindow->window_focus = ImGui::IsWindowFocused();
// 	// editorwindow->mouse_hover = ImGui::IsWindowHovered();

// 	editorwindow->pos.x = ImGui::GetWindowPos().x;
// 	editorwindow->pos.y = ImGui::GetWindowPos().y;
// 	editorwindow->size.x = ImGui::GetWindowSize().x;
// 	editorwindow->size.y = ImGui::GetWindowSize().y;

// 	ImGui::GetWindowDrawList()->AddImage((void*)editorwindow->framebuffer->texture->id, ImVec2(editorwindow->pos.x, editorwindow->pos.y), ImVec2(editorwindow->pos.x + editorwindow->size.x, editorwindow->pos.y + editorwindow->size.y), ImVec2(0, (float)editorwindow->size.y / window->size.y), ImVec2((float)editorwindow->size.x / window->size.x, 0));

// 	ImGui::End();
// }

