#include "MainRenderer.h"
#include <Engine/Window.h>
#include <Engine/Functions.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>

void lucy::MainRenderer::SetMaterial(lgl::Shader* shader, Material* material) {
	shader->SetUniformVec3("material.albedo", &material->albedo[0]);
	shader->SetUniformf("material.metallic", material->metallic);
	shader->SetUniformf("material.roughness", material->roughness);
	shader->SetUniformf("material.ao", 1.0f);
}

void lucy::MainRenderer::RenderFramebuffer(lgl::FrameBuffer* framebuffer) {
	framebuffer->UnBind();

	screen_shader->Bind();

	static auto* vertexarray = new lgl::VertexArray({});
	
	vertexarray->Bind();

	framebuffer->texture->BindUnit(0);
	screen_shader->SetUniformi("u_texture", 0);

	lgl::Draw(lgl::TRIANGLE, 0, 6);

	screen_shader->UnBind();
}

void lucy::MainRenderer::Render(Registry& registry) {
	auto& window = registry.store<Window>();
	auto& functions = registry.store<Functions>();

	if (window.framebuffer != nullptr)
		if (window.framebuffer->width != window.size.x || window.framebuffer->height != window.size.y) {
			free(window.framebuffer);
			window.framebuffer = nullptr;
		}

	if (window.framebuffer == nullptr)
		window.framebuffer = new lgl::FrameBuffer(window.size.x, window.size.y, false);

	lre::Clear({ 0, 0, 0, 0 });
	lgl::Viewport(0, 0, window.size.x, window.size.y);

	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		if (entity == functions.main_camera)
			camera.framebuffer = window.framebuffer;

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

		if (functions.render_target_to_screen)
			RenderFramebuffer(camera.framebuffer);
	}
}
