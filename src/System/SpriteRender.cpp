#include "MainRenderer.h"
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <Registry/Registry.h>

template <>
void lucy::MainRenderer::FlushSprite<lucy::MainRenderer::ColorVertex>() {
	auto& vertices = GetVertices<ColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	sprite_shader->SetUniformi("u_type", lre::COLOR);

	lre::RenderQuads(lgl::TRIANGLE, nullptr, ColorVertex::VertexArray(), vertexbuffer, vertices.size());

	vertices.clear();
}

template <>
void lucy::MainRenderer::FlushSprite<lucy::MainRenderer::TexVertex>() {
	auto& vertices = GetVertices<TexVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	sprite_shader->SetUniformi("u_type", lre::TEXTURE);

	lre::RenderQuads(lgl::TRIANGLE, nullptr, TexVertex::VertexArray(), vertexbuffer, vertices.size(), sprite_texture_store);

	sprite_texture_store.clear();
	vertices.clear();
}

template <>
void lucy::MainRenderer::FlushSprite<lucy::MainRenderer::TexColorVertex>() {
	auto& vertices = GetVertices<TexColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	sprite_shader->SetUniformi("u_type", lre::TEXTURE_COLOR);

	lre::RenderQuads(lgl::TRIANGLE, nullptr, TexColorVertex::VertexArray(), vertexbuffer, vertices.size(), sprite_texture_store);

	sprite_texture_store.clear();
	vertices.clear();
}

void lucy::MainRenderer::SpriteRender(Registry& registry) {
	auto& spriteregistry = registry.store<SpriteRegistry>();

	lre::SetModel(glm::mat4(1.0f));

	static lgl::Texture* null_texture = spriteregistry.GetNullTexture();

	for (auto& pair: sprite_material_entities) {
		if (pair.first == nullptr)
			sprite_shader->Bind();
		else {
			pbr_sprite_shader->Bind();
			SetMaterial(pbr_sprite_shader, pair.first);
		}

		for (const auto& entity: pair.second) {
			auto& spriterenderer = registry.get<SpriteRenderer>(entity);
			auto& transform = registry.get<Transform>(entity);

			auto* sprite = spriterenderer.sprite;

			if (sprite != nullptr) {
				if (!sprite_texture_store.slotavaliable()) {
					FlushSprite<TexVertex>();
				}
				uint32_t tex_id = (sprite->raw_texture->texture != nullptr) ? sprite->raw_texture->texture->id: spriteregistry.GetNullTexture()->id;

				if (spriterenderer.enable_color) {
					lre::QuadIndexed(GetVertices<TexColorVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.color, spriterenderer.uv0, spriterenderer.uv1, sprite_texture_store[tex_id], transform.GetRotationQuat());
				} else {
					lre::QuadIndexed(GetVertices<TexVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.uv0, spriterenderer.uv1, sprite_texture_store[tex_id], transform.GetRotationQuat());
				}
			} else {
				lre::QuadIndexed(GetVertices<ColorVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.color, transform.GetRotationQuat());
			}
		}

		FlushSprite<ColorVertex>();
		FlushSprite<TexVertex>();
		FlushSprite<TexColorVertex>();
	}

	sprite_shader->UnBind();
}