#include "SpriteRenderPass.h"
#include <iostream>
#include <Structures/Structures.h>
#include <Components/Components.h>

using TexVertex = lucy::Vertex::P1UV1T1;
using ColorVertex = lucy::Vertex::P1C1;
using TexColorVertex = lucy::Vertex::P1C1UV1T1;

static enum ShaderStates {
	TEXTURE,
	TEXTURE_COLOR,
	TEXTURE_UCOLOR,
	UTEXTURE,
	UTEXTURE_COLOR,
	UTEXTURE_UCOLOR,
	COLOR,
	UCOLOR,
};

void lucy::SpriteRenderPass::FirstInit() {
	
}

void lucy::SpriteRenderPass::Init() {
	
}

template <>
void lucy::SpriteRenderPass::Flush<ColorVertex>() {
	auto& vertices = GetVertices<ColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	shader->SetUniformi("u_type", COLOR);

	renderer.RenderQuads(lgl::TRIANGLE, nullptr, ColorVertex::VertexArray(), vertexbuffer, vertices.size());

	vertices.clear();
}

template <>
void lucy::SpriteRenderPass::Flush<TexVertex>() {
	auto& vertices = GetVertices<TexVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	shader->SetUniformi("u_type", TEXTURE);

	renderer.RenderQuads(lgl::TRIANGLE, nullptr, TexVertex::VertexArray(), vertexbuffer, vertices.size());

	texture_store.clear();
	vertices.clear();
}

template <>
void lucy::SpriteRenderPass::Flush<TexColorVertex>() {
	auto& vertices = GetVertices<TexColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	shader->SetUniformi("u_type", TEXTURE_COLOR);
	
	renderer.RenderQuads(lgl::TRIANGLE, nullptr, TexColorVertex::VertexArray(), vertexbuffer, vertices.size());

	texture_store.clear();
	vertices.clear();
}

void lucy::SpriteRenderPass::Flush() {
	shader->Bind();

	Flush<ColorVertex>();
	Flush<TexVertex>();
	Flush<TexColorVertex>();

	shader->UnBind();
}


void lucy::SpriteRenderPass::Render(lgl::FrameBuffer* framebuffer) {
	if (framebuffer != nullptr) framebuffer->Bind();

	if (shader == nullptr)
		shader = new lgl::Shader("D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\sprite.vert", "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\sprite.frag");

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

	Flush();

	if (framebuffer != nullptr) framebuffer->UnBind();
}

void lucy::SpriteRenderPass::Render(Camera& camera) {
	if (!camera.enable) return;

	renderer.SetProjection(camera.projection);
	renderer.SetView(camera.view);
	renderer.SetModel(glm::mat4(1.0f));

	Render(camera.framebuffer);
}

void lucy::SpriteRenderPass::Render() {
	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		Render(camera);
	}
}
