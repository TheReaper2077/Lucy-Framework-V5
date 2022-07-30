#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>
#include <Engine/Util.h>

lucy::Renderer::Renderer() {
	
}

lucy::Renderer::~Renderer() {
	
}

void lucy::Renderer::Init() {
	uniformbuffer = lgl::MakeUniformBuffer();

	uniformbuffer->Bind();
	uniformbuffer->Allocate(sizeof(glm::mat4) * 4);
	uniformbuffer->BindRange(0, sizeof(glm::mat4) * 4, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));
	SetViewPos(glm::vec3(0.0f));

	SetShader("mesh", "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Default\\mesh.vert", "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Default\\mesh.frag");
	SetShader("pbrmesh", "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Default\\mesh.vert", "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\Default\\pbr.frag");
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
	uniformbuffer->AddDataDynamic(&this->view_pos[0], sizeof(glm::mat4), sizeof(glm::mat4) * 3);
}

void lucy::Renderer::SetPerspective() {
	
}

void lucy::Renderer::SetOrtho(const float left, const float right, const float top, const float bottom, const float vnear, const float vfar) {
	SetProjection(glm::ortho<float>(left, right, top, bottom, vnear, vfar));
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
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void lucy::Renderer::Clear(const glm::vec3& color) {
	glClearColor(color.x, color.y, color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void lucy::Renderer::SetShader(const std::string& name, const std::string& vs_filename, const std::string& fs_filename) {
	shader_src_map[name] = std::pair(vs_filename, fs_filename);
}

lgl::Shader* lucy::Renderer::GetPBRShader(const std::string& name) {
	auto id = name + "_PBR_" + std::to_string(directional_light_count) + "_" + std::to_string(point_light_count);

	if (shader_map.find(id) == shader_map.end()) {
		const auto& [vs, fs] = shader_src_map[name];

		auto vs_src = util::read_file(vs);
		auto fs_src = util::read_file(fs);

		std::string uniforms, logic;

		for (int i = 0; i < directional_light_count; i++) {
			std::string dir_light = "dir_light" + std::to_string(i);
			uniforms += "uniform Light " + dir_light + ";\n";
			logic += "	Lo += DirCalculatePBR(N, V, " + dir_light + ".position, " + dir_light + ".direction, " + dir_light + ".color);\n";
		}
		for (int i = 0; i < point_light_count; i++) {
			auto point_light = "point_light" + std::to_string(i);
			uniforms += "uniform Light " + point_light + ";\n";
			logic += "	Lo += PointCalculatePBR(N, V, " + point_light + ".position, " + point_light + ".color);\n";
		}

		util::replace_first(fs_src, "#define SET_UNIFORMS", uniforms);
		util::replace_first(fs_src, "#define SET_LOGIC", logic);

		shader_map[id] = lgl::MakeShader(vs_src, fs_src, false);
	}

	return shader_map[id];
}

lgl::Shader* lucy::Renderer::GetShader(const std::string& name) {
	if (shader_map.find(name) == shader_map.end()) {
		const auto& [vs, fs] = shader_src_map[name];
	
		shader_map[name] = lgl::MakeShader(vs, fs);
	}

	return shader_map[name];
}

