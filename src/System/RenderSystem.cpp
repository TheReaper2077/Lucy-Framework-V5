#include "RenderSystem.h"



void lucy::System::RenderSystem(Registry& registry) {
	Clear({ 0, 0, 0, 0 });
	glViewport(0, 0, window.size.x, window.size.y);

	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		SetProjection(camera.projection);
		SetView(camera.view);
		SetViewPos(camera.position);

		Clear(camera.clear_color);
		glViewport(0, 0, window.size.x, window.size.y);

		// for (auto& pair: renderpass_map) {
		// 	pair.second->Init();
		// 	pair.second->Render(nullptr);
		// }
	}
}

