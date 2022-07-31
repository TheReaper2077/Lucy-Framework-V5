#include "RenderSprite.h"
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <Registry/Registry.h>

namespace lucy {
	template <typename T>
	std::vector<T>& GetVertices() {
		static std::vector<T> vector;
		return vector;
	}

	template <typename T>
	lgl::VertexBuffer* AddData(std::vector<T>& vertices) {
		static lgl::VertexBuffer vertexbuffer;

		vertexbuffer.Bind();
		vertexbuffer.Allocate(sizeof(T)*vertices.size());
		vertexbuffer.AddDataDynamic(vertices.data(), sizeof(T)*vertices.size());
		return &vertexbuffer;
	}

	template <typename T>
	lgl::VertexBuffer* AddData() {
		return AddData(GetVertices<T>());
	}

	template <typename T>
	void Flush(Renderer& renderer);
	void Flush(Renderer& renderer);
}

static lucy::TextureStore texture_store;
static lgl::Shader* shader = nullptr;

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

template <>
void lucy::Flush<ColorVertex>(Renderer& renderer) {
	auto& vertices = GetVertices<ColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	shader->SetUniformi("u_type", COLOR);

	renderer.RenderQuads(lgl::TRIANGLE, nullptr, ColorVertex::VertexArray(), vertexbuffer, vertices.size());

	vertices.clear();
}

template <>
void lucy::Flush<TexVertex>(Renderer& renderer) {
	auto& vertices = GetVertices<TexVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	shader->SetUniformi("u_type", TEXTURE);

	renderer.RenderQuads(lgl::TRIANGLE, nullptr, TexVertex::VertexArray(), vertexbuffer, vertices.size(), texture_store);

	texture_store.clear();
	vertices.clear();
}

template <>
void lucy::Flush<TexColorVertex>(Renderer& renderer) {
	auto& vertices = GetVertices<TexColorVertex>();
	if (vertices.size() == 0) return;

	auto* vertexbuffer = AddData(vertices);

	shader->SetUniformi("u_type", TEXTURE_COLOR);
	
	renderer.RenderQuads(lgl::TRIANGLE, nullptr, TexColorVertex::VertexArray(), vertexbuffer, vertices.size(), texture_store);

	texture_store.clear();
	vertices.clear();
}

void lucy::Flush(Renderer& renderer) {
	shader->Bind();

	Flush<ColorVertex>(renderer);
	Flush<TexVertex>(renderer);
	Flush<TexColorVertex>(renderer);

	shader->UnBind();
}

void lucy::RenderSprite(Registry& registry, Renderer renderer) {
	auto& spriteregistry = registry.store<SpriteRegistry>();

	renderer.SetModel(glm::mat4(1.0f));

	if (shader == nullptr)
		shader = lgl::MakeShader("D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Default\\sprite.vert", "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Default\\sprite.frag");

	static lgl::Texture* null_texture = spriteregistry.GetNullTexture();

	for (auto [entity, tag, transform, spriterenderer]: registry.view<Tag, Transform, SpriteRenderer>().each()) {
		auto* sprite = spriterenderer.sprite;

		if (sprite != nullptr) {
			if (!texture_store.slotavaliable()) {
				Flush<TexVertex>(renderer);









				saddddddddddddddddddddddddd
			}
			uint32_t tex_id = (sprite->raw_texture->texture != nullptr) ? sprite->raw_texture->texture->id: spriteregistry.GetNullTexture()->id;

			if (spriterenderer.enable_color) {
				Primitives::QuadIndexed(GetVertices<TexVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.uv0, spriterenderer.uv1, texture_store[tex_id], transform.GetRotationQuat());
			} else {
				Primitives::QuadIndexed(GetVertices<TexColorVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.color, spriterenderer.uv0, spriterenderer.uv1, texture_store[tex_id], transform.GetRotationQuat());
			}
		} else {
			Primitives::QuadIndexed(GetVertices<ColorVertex>(), transform.translation, { transform.scale.x, transform.scale.y }, spriterenderer.color, transform.GetRotationQuat());
		}
	}

	Flush(renderer);
}
