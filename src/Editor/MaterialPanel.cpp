#include "Panel.h"
#include <iostream>
#include <Registry/Registry.h>

void lucy::Panel<lucy::PanelInstance_MaterialRegistry>::Render() {
	if (!panel_open) return;

	auto& materialregistry = registry.store<MaterialRegistry>();

	if (ImGui::Begin("Material Registry", &panel_open)) {
		for (auto& pair: materialregistry.material_registry) {
			if (ImGui::TreeNodeEx(pair.second.name.c_str())) {
				ImGui::TreePop();
			}
		}

	}
	ImGui::End();
}