#include "MainRenderer.h"
#include <Engine/Window.h>
#include <Engine/Events.h>
#include <Engine/Functions.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <iostream>

void lucy::MainRenderer::SetMaterial(lgl::Shader* shader, Material* material) {
	shader->SetUniformVec3("material.albedo", &material->albedo[0]);
	shader->SetUniformf("material.metallic", material->metallic);
	shader->SetUniformf("material.roughness", material->roughness);
	shader->SetUniformf("material.ao", 1.0f);
}

void lucy::MainRenderer::RenderFramebuffer(const glm::vec2& window_size, lgl::FrameBuffer* framebuffer) {
	framebuffer->UnBind();

	screen_shader->Bind();

	static auto* vertexarray = new lgl::VertexArray({});
	
	vertexarray->Bind();

	framebuffer->texture->BindUnit(0);
	screen_shader->SetUniformi("u_texture", 0);

	glm::vec2 res_uv = { framebuffer->width / window_size.x, framebuffer->height / window_size.y };
	screen_shader->SetUniformVec2("res_uv", &res_uv[0]);

	lgl::Draw(lgl::TRIANGLE, 0, 6);

	screen_shader->UnBind();
}

void lucy::MainRenderer::Render(Registry& registry) {
	auto& gamewindow = registry.store<GameWindow>();
	auto& window = registry.store<Window>();
	auto& events = registry.store<Events>();
	auto& functions = registry.store<Functions>();

	render_resolution = gamewindow.size;

	if (gamewindow.framebuffer != nullptr) {
		if (gamewindow.framebuffer->width != render_resolution.x || gamewindow.framebuffer->height != render_resolution.y) {
			free(gamewindow.framebuffer);
			gamewindow.framebuffer = nullptr;
		}
	}

	if (gamewindow.framebuffer == nullptr) {
		gamewindow.framebuffer = new lgl::FrameBuffer(render_resolution.x, render_resolution.y, false);
	}

	lre::Clear({ 0, 0, 0, 0 });
	lgl::Viewport(0, 0, window.size.x, window.size.y);

	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		if (entity == functions.main_camera)
			camera.framebuffer = gamewindow.framebuffer;

		if (camera.framebuffer != nullptr)
			camera.framebuffer->Bind();

		lre::SetProjection(camera.projection);
		lre::SetView(camera.view);
		lre::SetViewPos(camera.position);

		lgl::Clear(camera.clear_color.x, camera.clear_color.y, camera.clear_color.z, camera.clear_color.w, camera.clear_flags);

		lgl::Viewport(0, 0, gamewindow.size.x, gamewindow.size.y);

		SetLightAndShaders(registry);

		// SpriteRender(registry);
		MeshRender(registry);
		// DebugRender(registry);

		if (camera.framebuffer != nullptr)
			camera.framebuffer->UnBind();

		if (functions.render_target_to_screen)
			RenderFramebuffer(gamewindow.size, camera.framebuffer);
	}

	if (events.IsWindowResized()) {
		window.size = events.GetWindowSize();
	}
	if (events.IsWindowMoved())
		window.pos = events.GetWindowPosition();
}
