#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"

namespace ImGui {
	std::tuple<float, float> ThumbnailListLogic(const float& padding, const float& thumbnail_size) {
		float cell_size = padding + thumbnail_size;
		float panel_width = ImGui::GetContentRegionAvail().x;

		int column_count = (int)(panel_width / cell_size);
		int width_delta = int(panel_width) - int(cell_size)*(int(panel_width)/int(cell_size));

		if (panel_width > cell_size) {
			ImGui::Columns(column_count, 0, false);

			for (int i = 1; i < column_count; i++)
				ImGui::SetColumnOffset(i, i * cell_size);
		}

		auto* draw_list = ImGui::GetWindowDrawList();
		auto win_pos = ImGui::GetWindowPos();

		int column_idx = 0;
		int row_idx = 1;

		float y_scroll = ImGui::GetScrollY();

		return { panel_width, cell_size };
	}
}

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
				if (editorstatus.selected_entity != (Entity)0)
					editorstatus.selected_entity = (Entity)0;
				if (editorstatus.selected_texture != pair_texture.second.id)
					editorstatus.selected_texture = pair_texture.second.id;
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