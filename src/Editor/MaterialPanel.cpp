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
		// static float padding = 15.0f;
		// static float thumbnail_size = 80;
		
		// auto [panel_width, cell_size] = ImGui::ThumbnailListLogic(padding, thumbnail_size);

		// for (auto pair_material: materialregistry.material_registry) {
		// 	// if (ImGui::ImageButton((void*)spriteregistry.GetNullTexture()->id, { thumbnail_size, thumbnail_size }, { 0, 0 }, { 1, 1 }, 1));

		// 	ImGui::Button(pair_material.second.name.c_str());

		// 	if (panel_width > cell_size) ImGui::NextColumn();
		// }
		// if (panel_width > cell_size) ImGui::Columns(1);

		// ImGui::DragFloat("Padding", &padding, 0.1, 1);
		// ImGui::DragFloat("Thumbnail", &thumbnail_size, 0.1, 1);
		for (auto& pair: materialregistry.material_registry) {
			auto& material = pair.second;

			if (ImGui::TreeNode(pair.second.name.c_str())) {
				ImGui::DragFloat3("albedo", &material.albedo[0], 0.01, 0, 1);
				ImGui::DragFloat3("diffuse", &material.diffuse[0], 0.01, 0, 1);
				ImGui::DragFloat3("ambient", &material.ambient[0], 0.01, 0, 1);
				ImGui::DragFloat3("specular", &material.specular[0], 0.01, 0, 1);
				
				ImGui::DragFloat("roughness", &material.roughness, 0.01, 0, 1);
				ImGui::DragFloat("metallic", &material.metallic, 0.01, 0, 1);
				ImGui::DragFloat("shininess", &material.shininess, 0.01, 0, 1);

				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}
