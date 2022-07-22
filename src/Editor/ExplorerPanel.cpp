#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"
#include <filesystem>
#include <iostream>
#include "Explorer.h"

static auto& registry = lucy::Registry::Instance();
static auto& spriteregistry = registry.store<lucy::SpriteRegistry>();
auto& editorstatus = registry.store<lucy::EditorStatus>();
auto& events = registry.store<lucy::Events>();

// void TextureDisp(std::string dirpath) {
// 	static float padding = 15.0f;
// 	static float thumbnail_size = 80;

// 	auto [panel_width, cell_size] = ImGui::ThumbnailListLogic(padding, thumbnail_size);

// 	for (auto pair_texture: spriteregistry.texture_store) {
// 		if (ImGui::ImageButton((void*)pair_texture.second.texture->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
// 			if (editorstatus.GetEntityID() != (lucy::Entity)0)
// 				editorstatus.SetEntity((lucy::Entity)0);
// 			if (editorstatus.GetTextureID() != pair_texture.second.id)
// 				editorstatus.SetTexture(pair_texture.second.id);
// 		}

// 		bool button_hovered = ImGui::IsItemHovered();

// 		ImGui::Text(pair_texture.second.name.c_str());

// 		if (ImGui::IsItemHovered() || button_hovered) {
// 			ImGui::BeginTooltip();
// 			ImGui::Text("Filename -");
// 			ImGui::SameLine();
// 				ImGui::Text(pair_texture.second.filename.c_str());
// 			ImGui::Text("Name -");
// 			ImGui::SameLine();
// 				ImGui::Text(pair_texture.second.name.c_str());
// 			ImGui::Text("ID -");
// 			ImGui::SameLine();
// 				ImGui::Text(pair_texture.second.id.c_str());
// 			ImGui::EndTooltip();
// 		}

// 		if (panel_width > cell_size) ImGui::NextColumn();
// 	}
// 	if (panel_width > cell_size) ImGui::Columns(1);

// 	// ImGui::DragFloat("Padding", &padding, 0.1, 1);
// 	// ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
// }

// void Explorer() {
// 	static float slider = 0.3;
// 	ImGui::SliderFloat("Column Size", &slider, 0.1f, 1.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
// 	float offset = ImGui::GetContentRegionAvail().x * .3;

// 	ImGui::Columns(2, 0, true);

// 	ImGui::BeginChild("##0");
// 	static std::string selected_path = "D:\\C++\\Lucy Framework V5\\assets\\";
// 	Directory("D:\\C++\\Lucy Framework V5\\assets\\", selected_path);
// 	ImGui::EndChild();

// 	ImGui::NextColumn();

// 	ImGui::BeginChild("##1");
// 	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
// 	ImGui::InputText("##", &selected_path);
// 	Textures(selected_path);
// 	TextureDisp(selected_path);

// 	ImGui::EndChild();
// }

template <>
void lucy::Panel<lucy::PanelInstance_Explorer>::Render() {
	if (!panel_open) return;

	if (ImGui::Begin("Explorer", &panel_open)) {
		static Explorer explorer;
		explorer.Render();
	}
	ImGui::End();
}