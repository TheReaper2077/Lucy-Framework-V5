#include "RenderSystem.h"
#include "RenderMesh.h"
#include "RenderSprite.h"
#include <Engine/Window.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <glad/glad.h>
#include "LightingSystem.h"

void lucy::System::RenderSystem(Registry& registry) {
	// LightingSystem(registry);

	auto& renderer = registry.store<Renderer>();
	auto& window = registry.store<Window>();

	renderer.Clear({ 0, 0, 0, 0 });
	glViewport(0, 0, window.size.x, window.size.y);

	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		renderer.SetProjection(camera.projection);
		renderer.SetView(camera.view);
		renderer.SetViewPos(camera.position);

		renderer.Clear(camera.clear_color);
		glViewport(0, 0, window.size.x, window.size.y);

		RenderSprite(registry, renderer);
		// MeshRenderSystem(registry, renderer);
	}
}
