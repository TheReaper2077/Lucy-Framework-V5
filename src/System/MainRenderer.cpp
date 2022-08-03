#include "MainRenderer.h"
#include <Engine/Window.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>

void lucy::MainRenderer::SetMaterial(lgl::Shader* shader, Material* material) {
	shader->SetUniformVec3("material.albedo", &material->albedo[0]);
	shader->SetUniformf("material.metallic", material->metallic);
	shader->SetUniformf("material.roughness", material->roughness);
	shader->SetUniformf("material.ao", 1.0f);
}

void lucy::MainRenderer::Render(Registry& registry) {
	auto& window = registry.store<Window>();

	lre::Clear({ 0, 0, 0, 0 });
	lgl::Viewport(0, 0, window.size.x, window.size.y);

	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		if (camera.framebuffer != nullptr)
			camera.framebuffer->Bind();

		lre::SetProjection(camera.projection);
		lre::SetView(camera.view);
		lre::SetViewPos(camera.position);

		lre::Clear(camera.clear_color);
		lgl::Viewport(0, 0, window.size.x, window.size.y);

		SetLightAndShaders(registry);

		SpriteRender(registry);
		MeshRender(registry);
		DebugRender(registry);

		if (camera.framebuffer != nullptr)
			camera.framebuffer->UnBind();
	}
}
