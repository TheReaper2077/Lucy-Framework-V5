#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"
#include <filesystem>
#include <iostream>
#include "Explorer.h"

template <>
void lucy::Panel<lucy::PanelInstance_Explorer>::Render() {
	if (!panel_open) return;

	if (ImGui::Begin("Explorer", &panel_open)) {
		static Explorer explorer;
		explorer.Render();
	}
	ImGui::End();
}