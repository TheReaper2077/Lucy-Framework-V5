#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

template <>
void lucy::Panel<lucy::PanelInstance_Explorer>::Render() {
	if (!panel_open) return;

	auto& editorstatus = registry.store<EditorStatus>();
	auto& events = registry.store<Events>();
	auto& spriteregistry = registry.store<SpriteRegistry>();

	// spriteregistry.GetTexture();

	if (ImGui::Begin("Explorer", &panel_open)) {
		for (const std::filesystem::path& entry: std::filesystem::directory_iterator(std::filesystem::current_path())) {
			ImGui::Button(entry);
		}
	}
	ImGui::End();
}