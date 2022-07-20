#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"

template <>
void lucy::Panel<lucy::PanelInstance_MaterialRegistry>::Render() {
	if (!panel_open) return;

	auto& editorstatus = registry.store<EditorStatus>();
	auto& events = registry.store<Events>();
	auto& materialregistry = registry.store<MaterialRegistry>();
	auto& spriteregistry = registry.store<SpriteRegistry>();
	auto& texture = registry.store<lgl::Texture>();
	

	if (ImGui::Begin("Material Registry", &panel_open)) {
		static float padding = 15.0f;
		static float thumbnail_size = 80;
		
		auto [panel_width, cell_size] = ImGui::ThumbnailListLogic(padding, thumbnail_size);

		for (auto pair_material: materialregistry.material_registry) {
			if (ImGui::ImageButton((void*)spriteregistry.GetNullTexture(), { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1)) {
				
			}

			ImGui::Text(pair_material.second.name.c_str());

			if (panel_width > cell_size) ImGui::NextColumn();
		}
		if (panel_width > cell_size) ImGui::Columns(1);

		ImGui::DragFloat("Padding", &padding, 0.1, 1);
		ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
	}
	ImGui::End();
}