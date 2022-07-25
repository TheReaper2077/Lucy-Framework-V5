#include "Panel.h"

#include <Registry/Registry.h>
#include <Engine/Events.h>
#include "EditorStatus.h"

template <>
void lucy::Panel<lucy::PanelInstance_MeshRegistry>::Render() {
	if (!panel_open) return;

	auto& editorstatus = registry.store<EditorStatus>();
	auto& events = registry.store<Events>();
	auto& materialregistry = registry.store<MaterialRegistry>();
	auto& spriteregistry = registry.store<SpriteRegistry>();
	auto& texture = registry.store<lgl::Texture>();
	

	if (ImGui::Begin("Mesh Registry", &panel_open)) {
		
	}
	ImGui::End();
}