#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>
#include "ECS.h"
#include "Util.h"
#include <Components/Components.h>

auto& registry = lucy::Registry::Instance();

lucy::Renderer::Renderer() {
	uniformbuffer = new lgl::UniformBuffer();

	uniformbuffer->Bind();
	uniformbuffer->Allocate(sizeof(glm::mat4) * 4);
	uniformbuffer->BindRange(0, sizeof(glm::mat4) * 4, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));
	SetViewPos(glm::vec3(0.0f));
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

void lucy::Renderer::SetViewPos(const glm::vec3& view_pos) {
	if (this->view_pos == view_pos) return;
	this->view_pos = view_pos;
	uniformbuffer->AddDataDynamic(&this->view_pos[0], sizeof(glm::vec3), sizeof(glm::mat4) * 3);
}

void lucy::Renderer::SetPerspective() {
	
}

void lucy::Renderer::SetOrtho(const float left, const float right, const float top, const float bottom, const float near, const float far) {
	SetProjection(glm::ortho<float>(left, right, top, bottom, near, far));
}

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count) {
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

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures) {
	textures.bind();

	Render(primitive, shader, vertexarray, vertexbuffer, first, count);
}

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count) {
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

void lucy::Renderer::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures) {
	textures.bind();

	Render(primitive, shader, vertexarray, vertexbuffer, indexbuffer, count);
}

void lucy::Renderer::RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int vertexcount) {
	Render(primitive, shader, vertexarray, vertexbuffer, Primitives::GetQuadIndices(vertexcount), vertexcount*1.5);
}

void lucy::Renderer::RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int vertexcount, TextureStore& textures) {
	Render(primitive, shader, vertexarray, vertexbuffer, Primitives::GetQuadIndices(vertexcount), vertexcount*1.5, textures);
}

void lucy::Renderer::Clear(const glm::vec4& color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void lucy::Renderer::Clear(const glm::vec3& color) {
	glClearColor(color.r, color.g, color.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void lucy::Renderer::AddShader(const std::string& name, const std::string& vs_filename, const std::string& fs_filename) {
	shader_src_map[name] = std::pair(vs_filename, fs_filename);
}

lgl::Shader& lucy::Renderer::GetPBRShader(const std::string& name) {
	int dir_count = 0, point_count = 0; 

	for (auto [entity, tag, light]: registry.view<Tag, Light>().each()) {
		dir_count += (light.mode == DIRECTIONAL_LIGHT);
		point_count += (light.mode == POINT_LIGHT);
	}

	auto id = name + "_PBR_" + std::to_string(dir_count) + "_" + std::to_string(point_count);

	if (shader_map.find(id) != shader_map.end())
		return shader_map[id];

	const auto& [vs, fs] = shader_src_map[name];

	auto vs_src = util::ReadFile(vs);
	auto fs_src = util::ReadFile(fs);

	std::string uniforms, logic;

	for (int i = 0; i < dir_count; i++) {
		uniforms += "uniform Light dir_light" + std::to_string(i) + ";\n";
		logic += "	Lo += DirCalculatePBR(N, V, dir_light" + std::to_string(i) + ".position, dir_light" + std::to_string(i) + ".direction, dir_light" + std::to_string(i) + ".color);\n";
	}
	for (int i = 0; i < point_count; i++) {
		uniforms += "uniform Light point_light" + std::to_string(i) + ";\n";
		logic += "	Lo += PointCalculatePBR(N, V, point_light" + std::to_string(i) + ".position, point_light" + std::to_string(i) + ".color);\n"\
	}
}
