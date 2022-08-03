#include "MainRenderer.h"
#include <Components/Components.h>
#include <Engine/Functions.h>

// template <typename T>
// void RenderType(std::vector<T>& vertices, lucy::RenderContext& renderer) {
// 	if (vertices.size()) {
// 		if (shader == nullptr)
// 			shader = renderer.GetShader("sprite");
			
// 		if (vertexbuffer == nullptr)
// 			vertexbuffer = lgl::MakeVertexBuffer();

// 		shader->Bind();

// 		shader->SetUniformi("u_type", lucy::ShaderStates::UCOLOR);
// 		shader->SetUniformVec4("u_color", &wireframe_color[0]);

// 		vertexbuffer->Allocate(sizeof(T) * vertices.size());
// 		vertexbuffer->AddDataDynamic(vertices.data(), sizeof(T) * vertices.size());

// 		renderer.Render(lgl::LINE, nullptr, T::VertexArray(), vertexbuffer, lucy::Primitives::GetWireQuadIndices(vertices.size()), vertices.size() * 2);

// 		shader->UnBind();

// 		vertices.clear();
// 	}
// }

// typedef lre::Vertex::P1C1 LineVertex;

// template <>
// void lucy::MainRenderer::Flush<LineVertex>() {
// 	auto& vertices = GetVertices<LineVertex>();
// 	if (vertices.size() == 0) return;

// 	auto* vertexbuffer = AddData(vertices);

// 	sprite_shader->SetUniformi("u_type", lre::TEXTURE_COLOR);

// 	lre::RenderQuads(lgl::TRIANGLE, nullptr, LineVertex::VertexArray(), vertexbuffer, vertices.size(), sprite_texture_store);

// 	sprite_texture_store.clear();
// 	vertices.clear();
// }

void lucy::MainRenderer::DebugRender(Registry& registry) {
	auto& functions = registry.store<Functions>();

	lre::SetModel(glm::mat4(1.0f));

	// if (functions.enable_debug_render) {
	// 	for (auto [entity, transform, bc2d]: registry.view<Transform, BoxCollider2D>().each()) {
	// 		lre::QuadIndexed(GetVertices<LineVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, { 1, 1, 0, 1});
	// 	}

	// 	Flush<LineVertex>();
	// }
}