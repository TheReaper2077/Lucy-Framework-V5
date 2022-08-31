#include "RenderSystem.h"
#include <Lucy/State.h>
#include <LucyRE/LucyRE.h>
#include <Lucy/ECS.h>
#include <iostream>
#include <Structures/Structures.h>
#include <Lucy/MeshRegistry.h>

static auto& registry = lucy::Registry::Instance();

// void Test() {
// 	lre::Vertex::P1N1 test_vertices[] = {
// 		{{ -0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
// 		{{ -0.5, +0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
// 		{{ +0.5, +0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
// 		{{ +0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
// 	};

// 	uint32_t test_indices[] = {
// 		0 + 4 * 0, 1 + 4 * 0, 2 + 4 * 0, 2 + 4 * 0, 3 + 4 * 0, 0 + 4 * 0,
// 	};

// 	static lgl::VertexArray* vertexarray = lre::Vertex::P1N1::VertexArray();
// 	static lgl::VertexBuffer* vertexbuffer = nullptr;
// 	static lgl::IndexBuffer* indexbuffer = nullptr;

// 	if (vertexbuffer == nullptr) {
// 		vertexbuffer = new lgl::VertexBuffer();

// 		vertexbuffer->Bind();
// 		vertexbuffer->Allocate(sizeof(test_vertices));
// 		vertexbuffer->AddDataDynamic(test_vertices, sizeof(test_vertices));
// 	}

// 	if (indexbuffer == nullptr) {
// 		indexbuffer = new lgl::IndexBuffer();

// 		indexbuffer->Bind();
// 		indexbuffer->Allocate(sizeof(test_indices));
// 		indexbuffer->AddData(test_indices, sizeof(test_indices));
// 	}

// 	auto* shader = lre::GetShader("normal");
// 	shader->Bind();

// 	vertexarray->Bind();
// 	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
// 	vertexarray->BindIndexBuffer(indexbuffer);

// 	lgl::DrawIndexed(lgl::TRIANGLE, 6, lgl::UNSIGNED_INT, nullptr);
// }

namespace lucy {
	void Render() {
		lre::SetModel(glm::mat4(1.0f));

		auto* shader = lre::GetShader("phong");
		shader->Bind();

		for (auto [entity, transform, light]: registry.view<Transform, Light>().each()) {
			glm::vec4 light_pos;
			if (light.mode == DIRECTIONAL_LIGHT)
				light_pos = { glm::normalize(transform.GetRotationQuat() * glm::vec3(0, 1, 0)), 0 };
			if (light.mode == POINT_LIGHT)
				light_pos = { transform.translation, 1 };

			shader->SetUniformVec4("light.color", &light.color[0]);
			shader->SetUniformVec4("light.pos", &light_pos[0]);
			shader->SetUniformf("light.ambient", light.ambient);
			shader->SetUniformf("light.diffuse", light.diffuse);
			shader->SetUniformf("light.specular", light.specular);

			break;
		}

		for (auto [entity, transform, meshrenderer]: registry.view<Transform, MeshRenderer>().each()) {
			if (meshrenderer.material != nullptr) {
				shader->SetUniformVec3("material.ambient", &meshrenderer.material->ambient[0]);
				shader->SetUniformVec3("material.specular", &meshrenderer.material->specular[0]);
				shader->SetUniformVec3("material.diffuse", &meshrenderer.material->diffuse[0]);
				shader->SetUniformf("material.shininess", meshrenderer.material->shininess);
			}
			if (meshrenderer.mesh != nullptr) {
				lre::SetModel(transform.GetModelMatrix());

				meshrenderer.mesh->vertexarray->Bind();
				meshrenderer.mesh->vertexarray->BindVertexBuffer(meshrenderer.mesh->vertexbuffer, meshrenderer.mesh->vertexarray->stride);
				meshrenderer.mesh->vertexarray->BindIndexBuffer(meshrenderer.mesh->indexbuffer);

				lgl::DrawIndexed(lgl::TRIANGLE, meshrenderer.mesh->indexcount, lgl::UNSIGNED_INT, nullptr);
			}
		}
	}
}

void lucy::System::RenderSystem() {
	auto& window = registry.store<Window>();
	auto& state = registry.store<State>();

	if (window.framebuffer == nullptr) {
		window.framebuffer = new lgl::FrameBuffer(window.size.x, window.size.y, false);
	}

	int w = 0, h = 0;
	lre::Clear({ 0, 0, 0, 1}, lgl::COLOR_BUFFER_BIT | lgl::DEPTH_BUFFER_BIT);
	SDL_GetWindowSize(window.sdl_window, &w, &h);
	lgl::Viewport(0, 0, w, h);

	for (auto [entity, transform, camera]: registry.view<Transform, Camera>().each()) {
		if (!camera.enable || camera.framebuffer == nullptr) continue;

		camera.framebuffer->Bind();

		lre::SetProjection(camera.projection);
		lre::SetView(camera.view);
		lre::SetViewPosition(camera.position);

		lre::Clear(camera.clear_color, camera.clear_flags);
		lgl::Viewport(0, 0, camera.width, camera.height);

		Render();

		camera.framebuffer->UnBind();

		if (state.render_to_screen) {
			lre::RenderFrameBufferToScreen(camera.framebuffer, window.size);
		}
	}
}
