#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>
#include <Engine/Util.h>

namespace lre {
	RenderContext re_context;
}

void lre::Initialize() {
	assert(lgl::IsInitialized());

	re_context.uniformbuffer = lgl::MakeUniformBuffer();

	re_context.uniformbuffer->Bind();
	re_context.uniformbuffer->Allocate(sizeof(glm::mat4) * 4);
	re_context.uniformbuffer->BindRange(0, sizeof(glm::mat4) * 4, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));
	SetViewPos(glm::vec3(0.0f));
}

void lre::SetModel(const glm::mat4& model) {
	if (re_context.model == model) return;
	re_context.model = model;
	re_context.uniformbuffer->AddDataDynamic(&re_context.model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}

void lre::SetView(const glm::mat4& view) {
	if (re_context.view == view) return;
	re_context.view = view;
	re_context.uniformbuffer->AddDataDynamic(&re_context.view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}

void lre::SetProjection(const glm::mat4& projection) {
	if (re_context.projection == projection) return;
	re_context.projection = projection;
	re_context.uniformbuffer->AddDataDynamic(&re_context.projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}

void lre::SetViewPos(const glm::vec3& view_pos) {
	if (re_context.view_pos == view_pos) return;
	re_context.view_pos = view_pos;
	re_context.uniformbuffer->AddDataDynamic(&re_context.view_pos[0], sizeof(glm::mat4), sizeof(glm::mat4) * 3);
}

void lre::SetPerspective(float fovy, float aspect, float vnear, float vfar) {
	SetProjection(glm::perspective(fovy, aspect, vnear, vfar));
}

void lre::SetOrtho(const float left, const float right, const float top, const float bottom, const float vnear, const float vfar) {
	SetProjection(glm::ortho<float>(left, right, top, bottom, vnear, vfar));
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count) {
	if (vertexarray && vertexbuffer && indexbuffer) {
		if (shader != nullptr)
			shader->Bind();
		vertexarray->Bind();
		vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
		vertexarray->BindIndexBuffer(indexbuffer);

		lgl::DrawIndexed(primitive, count, lgl::UNSIGNED_INT, nullptr);
	} else {
		assert(false);
	}
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures) {
	textures.bind();

	Render(primitive, shader, vertexarray, vertexbuffer, first, count);
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count) {
	if (vertexarray && vertexbuffer) {
		if (shader != nullptr)
			shader->Bind();
		vertexarray->Bind();
		vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);

		lgl::Draw(primitive, first, count);
	} else {
		assert(false);
	}
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures) {
	textures.bind();

	Render(primitive, shader, vertexarray, vertexbuffer, indexbuffer, count);
}

void lre::RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int vertexcount) {
	Render(primitive, shader, vertexarray, vertexbuffer, GetQuadIndices(vertexcount), vertexcount*1.5);
}

void lre::RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int vertexcount, TextureStore& textures) {
	Render(primitive, shader, vertexarray, vertexbuffer, GetQuadIndices(vertexcount), vertexcount*1.5, textures);
}

void lre::Clear(const glm::vec4& color) {
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void lre::Clear(const glm::vec3& color) {
	glClearColor(color.x, color.y, color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// void lre::SetShader(const std::string& name, const std::string& vs_filename, const std::string& fs_filename) {
// 	shader_src_map[name] = std::pair(vs_filename, fs_filename);
// }

