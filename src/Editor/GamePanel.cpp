#include "Panel.h"
#include <imgui.h>
#include <Engine/ECS.h>
#include <Engine/Window.h>
#include <Registry/Registry.h>

static auto& registry = lucy::Registry::Instance();

void lucy::Panel<lucy::PanelInstance_Game>::Render() {
	if (!panel_open) return;
	
	auto* window = registry.store<WindowRegistry>()[MAIN_WINDOW];
	auto* gamewindow = registry.store<WindowRegistry>()[GAME_WINDOW];

	if (gamewindow->framebuffer == nullptr) assert(false);
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(gamewindow->title.c_str(), &panel_open);
	ImGui::PopStyleVar();

	gamewindow->pos.x = ImGui::GetWindowPos().x;
	gamewindow->pos.y = ImGui::GetWindowPos().y;
	gamewindow->size.x = ImGui::GetWindowSize().x;
	gamewindow->size.y = ImGui::GetWindowSize().y;

	ImGui::GetWindowDrawList()->AddImage((void*)gamewindow->framebuffer->texture->id, ImVec2(gamewindow->pos.x, gamewindow->pos.y), ImVec2(gamewindow->pos.x + gamewindow->size.x, gamewindow->pos.y + gamewindow->size.y), ImVec2(0, (float)gamewindow->size.y / window->size.y), ImVec2((float)gamewindow->size.x / window->size.x, 0));
	ImGui::End();
}
