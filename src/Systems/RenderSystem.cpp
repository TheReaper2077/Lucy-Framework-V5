#include "RenderSystem.h"
#include <LucyRE/LucyRE.h>
#include <Lucy/ECS.h>
#include <Structures/Structures.h>

static auto& registry = lucy::Registry::Instance();
static auto& window = registry.store<lucy::Window>();

void Test() {
	lre::Vertex::P1N1 test_vertices[] = {
		{{ -0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
		{{ -0.5, +0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
		{{ +0.5, +0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
		{{ +0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }},
	};

	uint32_t test_indices[] = {
		0 + 4 * 0, 1 + 4 * 0, 2 + 4 * 0, 2 + 4 * 0, 3 + 4 * 0, 0 + 4 * 0,
	};

	static lgl::VertexArray* vertexarray = lre::Vertex::P1N1::VertexArray();
	static lgl::VertexBuffer* vertexbuffer = nullptr;
	static lgl::IndexBuffer* indexbuffer = nullptr;

	if (vertexbuffer == nullptr) {
		vertexbuffer = new lgl::VertexBuffer();

		vertexbuffer->Bind();
		vertexbuffer->Allocate(sizeof(test_vertices));
		vertexbuffer->AddDataDynamic(test_vertices, sizeof(test_vertices));
	}

	if (indexbuffer == nullptr) {
		indexbuffer = new lgl::IndexBuffer();

		indexbuffer->Bind();
		indexbuffer->Allocate(sizeof(test_indices));
		indexbuffer->AddData(test_indices, sizeof(test_indices));
	}

	auto* shader = lre::GetShader("normal");
	shader->Bind();

	vertexarray->Bind();
	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
	vertexarray->BindIndexBuffer(indexbuffer);

	lgl::DrawIndexed(lgl::TRIANGLE, 6, lgl::UNSIGNED_INT, nullptr);
}

namespace lucy {
	void Render() {
		lre::SetModel(glm::mat4(1.0f));

		Test();

		for (auto [entity, transform, meshrenderer]: registry.view<Transform, MeshRenderer>().each()) {

		}
	}
}

void lucy::System::RenderSystem() {
	if (window.framebuffer == nullptr) {
		window.framebuffer = new lgl::FrameBuffer(window.size.x, window.size.y, false);
	}

	lre::Clear({ 0, 0, 0, 1}, lgl::COLOR_BUFFER_BIT);
	lgl::Viewport(0, 0, window.pos.x, window.pos.y);

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
	}
}