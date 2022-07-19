// #include "Panel.h"

// static auto& registry = lucy::Registry::Instance();

// void ListLogic(bool& panel_open, const char* name) {
// 	if (!panel_open) return;

// 	auto& editorstatus = registry.store<EditorStatus>();
// 	auto& events = registry.store<Events>();
// 	auto& spriteregistry = registry.store<SpriteRegistry>();

// 	if (ImGui::Begin("Texture Registry", &panel_open)) {
// 		static float padding = 15.0f;
// 		static float thumbnail_size = 80;
// 		float cell_size = padding + thumbnail_size;

// 		float panel_width = ImGui::GetContentRegionAvail().x;
// 		int column_count = (int)(panel_width / cell_size);
// 		int width_delta = int(panel_width) - int(cell_size)*(int(panel_width)/int(cell_size));

// 		if (panel_width > cell_size) {
// 			ImGui::Columns(column_count, 0, false);

// 			for (int i = 1; i < column_count; i++)
// 				ImGui::SetColumnOffset(i, i*cell_size);
// 		}

// 		auto* draw_list = ImGui::GetWindowDrawList();
// 		auto win_pos = ImGui::GetWindowPos();

// 		int column_idx = 0;
// 		int row_idx = 1;

// 		float y_scroll = ImGui::GetScrollY();

// 		for (auto pair_texture: spriteregistry.texture_store) {
// 			// auto pos = ImGui::GetCursorPos();

// 			// pos.x += win_pos.x;
// 			// pos.y += win_pos.y;

// 			// if (ImGui::ImageButton((void*)pair_texture.second.texture->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
// 			// 	if (editorstatus.selected_entity != (Entity)0)
// 			// 		editorstatus.selected_entity = (Entity)0;
// 			// 	if (editorstatus.selected_texture != pair_texture.second.id)
// 			// 		editorstatus.selected_texture = pair_texture.second.id;
// 			// }

// 			// bool button_hovered = ImGui::IsItemHovered();

// 			// ImGui::Text(pair_texture.second.name.c_str());

// 			// if (ImGui::IsItemHovered() || button_hovered) {
// 			// 	ImGui::BeginTooltip();
// 			// 	ImGui::Text("Filename -");
// 			// 	ImGui::SameLine();
// 			// 		ImGui::Text(pair_texture.second.filename.c_str());
// 			// 	ImGui::Text("Name -");
// 			// 	ImGui::SameLine();
// 			// 		ImGui::Text(pair_texture.second.name.c_str());
// 			// 	ImGui::Text("ID -");
// 			// 	ImGui::SameLine();
// 			// 		ImGui::Text(pair_texture.second.id.c_str());
// 			// 	ImGui::EndTooltip();
// 			// }

// 			if (panel_width > cell_size) ImGui::NextColumn();
// 		}
// 		if (panel_width > cell_size) ImGui::Columns(1);

// 		ImGui::DragFloat("Padding", &padding, 0.1, 1);
// 		ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
// }