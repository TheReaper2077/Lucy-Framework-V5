#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"

template <>
void lucy::Panel<lucy::PanelInstance_TextureRegistry>::Render() {
	if (!panel_open) return;

	auto& editorstatus = registry.store<EditorStatus>();
	auto& events = registry.store<Events>();
	auto& spriteregistry = registry.store<SpriteRegistry>();

	if (ImGui::Begin("Texture Registry", &panel_open)) {
		static float padding = 15.0f;
		static float thumbnail_size = 80;

		auto [panel_width, cell_size] = ImGui::ThumbnailListLogic(padding, thumbnail_size);

		for (auto pair_texture: spriteregistry.texture_store) {
			if (ImGui::ImageButton((void*)pair_texture.second.texture->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
				if (editorstatus.GetEntityID() != (Entity)0)
					editorstatus.SetEntity((Entity)0);
				if (editorstatus.GetTextureID() != pair_texture.second.id)
					editorstatus.SetTexture(pair_texture.second.id);
			}

			bool button_hovered = ImGui::IsItemHovered();

			ImGui::Text(pair_texture.second.name.c_str());

			if (ImGui::IsItemHovered() || button_hovered) {
				ImGui::BeginTooltip();
				ImGui::Text("Filename -");
				ImGui::SameLine();
					ImGui::Text(pair_texture.second.filename.c_str());
				ImGui::Text("Name -");
				ImGui::SameLine();
					ImGui::Text(pair_texture.second.name.c_str());
				ImGui::Text("ID -");
				ImGui::SameLine();
					ImGui::Text(pair_texture.second.id.c_str());
				ImGui::EndTooltip();
			}

			if (panel_width > cell_size) ImGui::NextColumn();
		}
		if (panel_width > cell_size) ImGui::Columns(1);

		ImGui::DragFloat("Padding", &padding, 0.1, 1);
		ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
	}
	ImGui::End();
}