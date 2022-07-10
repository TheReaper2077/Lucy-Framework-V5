#include "SpriteRenderPass.h"
#include <iostream>
#include <Structures/Structures.h>
#include <Components/Components.h>

using TexVertex = lucy::Vertex::P1UV1I1;
using ColorVertex = lucy::Vertex::P1C1;
using TexColorVertex = lucy::Vertex::P1C1UV1I1;

void lucy::SpriteRenderPass::FirstInit() {
	
}

void lucy::SpriteRenderPass::Init() {
	
}

template <>
void lucy::SpriteRenderPass::Flush<ColorVertex>() {
	auto& vertices = GetVertices<ColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	renderer.RenderQuads(COLOR, ColorVertex::VertexArray(), vertexbuffer, vertices.size());

	vertices.clear();
}

template <>
void lucy::SpriteRenderPass::Flush<TexVertex>() {
	auto& vertices = GetVertices<TexVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	renderer.RenderQuads(TEXTURE, TexVertex::VertexArray(), vertexbuffer, vertices.size());

	texture_store.clear();
	vertices.clear();
}

template <>
void lucy::SpriteRenderPass::Flush<TexColorVertex>() {
	auto& vertices = GetVertices<TexColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	renderer.RenderQuads(TEXTURE | COLOR, TexColorVertex::VertexArray(), vertexbuffer, vertices.size());

	texture_store.clear();
	vertices.clear();
}


void lucy::SpriteRenderPass::Render() {
	static lgl::Texture* null_texture = nullptr;

	if (null_texture == nullptr) {
		null_texture = new lgl::Texture();
		null_texture->Bind();
		null_texture->LoadTexture(nullptr);
	}

	for (auto [entity, tag, transform, spriterenderer]: registry.view<Tag, Transform, SpriteRenderer>().each()) {
		auto* sprite = spriterenderer.sprite;

		if (sprite != nullptr) {
			if (!texture_store.slotavaliable()) {
				Flush<TexVertex>();
			}
			if (sprite->texture == nullptr) {
				Primitives::QuadIndexed(GetVertices<TexVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, sprite->uv0 * spriterenderer.uv0, sprite->uv1 * spriterenderer.uv1, texture_store[null_texture], transform.GetRotationQuat());
			} else {
				Primitives::QuadIndexed(GetVertices<TexVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, sprite->uv0 * spriterenderer.uv0, sprite->uv1 * spriterenderer.uv1, texture_store[spriterenderer.sprite->texture], transform.GetRotationQuat());
			}
		} else {
			Primitives::QuadIndexed(GetVertices<ColorVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.color, transform.GetRotationQuat());
		}
	}

	Flush<TexVertex>();
	Flush<ColorVertex>();
}
