#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

lucy::Renderer::Renderer() {
	uniformbuffer = new lgl::UniformBuffer();

	uniformbuffer->Bind();
	uniformbuffer->Allocate(sizeof(glm::mat4)*3);
	uniformbuffer->BindRange(0, sizeof(glm::mat4)*3, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));
}

lucy::Renderer::~Renderer() {
	
}

void lucy::Renderer::SetModel(const glm::mat4& model) {
	if (this->model == model) return;
	this->model = model;
	uniformbuffer->AddDataDynamic(&this->model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}

void lucy::Renderer::SetView(const glm::mat4& view) {
	if (this->view == view) return;
	this->view = view;
	uniformbuffer->AddDataDynamic(&this->view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}

void lucy::Renderer::SetProjection(const glm::mat4& projection) {
	if (this->projection == projection) return;
	this->projection = projection;
	uniformbuffer->AddDataDynamic(&this->projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}

void lucy::Renderer::SetPerspective() {
	
}

void lucy::Renderer::SetOrtho(const float left, const float right, const float top, const float bottom, const float near, const float far) {
	SetProjection(glm::ortho<float>(left, right, top, bottom, near, far));
}

void lucy::Renderer::RenderQuads(lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount) {
	Render(lgl::TRIANGLE, shader, vertexarray, vertexbuffer, Primitives::GetQuadIndices(vertexcount), vertexcount*1.5);
}

void lucy::Renderer::RenderQuads(lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, TextureStore& texture_store) {
	Render(lgl::TRIANGLE, shader, vertexarray, vertexbuffer, Primitives::GetQuadIndices(vertexcount), vertexcount*1.5, texture_store);
}

void lucy::Renderer::RenderTextureIdQuads(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, TextureStore& texture_store) {
	auto* shader = shaderregistry.GetShader(ShaderFlag::TEXTUREID);
	RenderQuads(shader, vertexarray, vertexbuffer, vertexcount, texture_store);
}

void lucy::Renderer::RenderTextureIdQuads(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount) {
	auto* shader = shaderregistry.GetShader(ShaderFlag::TEXTUREID);
	RenderQuads(shader, vertexarray, vertexbuffer, vertexcount);
}

void lucy::Renderer::RenderUniformTextureIdQuads(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, int textureid) {
	auto* shader = shaderregistry.GetShader(ShaderFlag::U_TEXTUREID);
	shader->Bind();
	shader->SetUniformi("u_textureid", textureid);

	RenderQuads(shader, vertexarray, vertexbuffer, vertexcount);
}

void lucy::Renderer::RenderUniformColor(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, const glm::vec4& color) {
	auto* shader = shaderregistry.GetShader(ShaderFlag::U_COLOR);
	shader->Bind();
	shader->SetUniformVec4("u_color", &color[0]);

	RenderQuads(shader, vertexarray, vertexbuffer, vertexcount);
}

void lucy::Renderer::RenderColor(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount) {
	auto* shader = shaderregistry.GetShader(ShaderFlag::COLOR);

	RenderQuads(shader, vertexarray, vertexbuffer, vertexcount);
}

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count) {
	shader->Bind();
	vertexarray->Bind();
	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
	vertexarray->BindIndexBuffer(indexbuffer);

	lgl::DrawIndexed(primitive, count, lgl::UNSIGNED_INT, nullptr);
}

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures) {
	textures.Bind();

	Render(primitive, shader, vertexarray, vertexbuffer, first, count);
}

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count) {
	shader->Bind();
	vertexarray->Bind();
	vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);

	lgl::Draw(primitive, first, count);
}

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures) {
	textures.Bind();

	Render(primitive, shader, vertexarray, vertexbuffer, indexbuffer, count);
}
