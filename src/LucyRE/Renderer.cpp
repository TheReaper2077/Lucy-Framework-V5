#include "Renderer.h"
#include "DrawList.h"
#include "Vertex.h"
#include <iostream>

#define self lre::Renderer::Instance()

#include <filesystem>

#define SHADER_PATH(rel_filepath) std::filesystem::current_path().string() + "\\Shaders\\" + std::string(rel_filepath)

void lre::SetModel(const glm::mat4& model) {
	if (self->model == model) return;
	self->model = model;
	self->uniformbuffer->AddDataDynamic(&self->model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}

void lre::SetView(const glm::mat4& view) {
	if (self->view == view) return;
	self->view = view;
	self->uniformbuffer->AddDataDynamic(&self->view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}

void lre::SetProjection(const glm::mat4& projection) {
	if (self->projection == projection) return;
	self->projection = projection;
	self->uniformbuffer->AddDataDynamic(&self->projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}

void lre::SetViewPosition(const glm::vec3& view_position) {
	if (self->view_position == view_position) return;
	self->view_position = view_position;
	self->uniformbuffer->AddDataDynamic(&self->view_position[0], sizeof(glm::vec3), sizeof(glm::mat4) * 3);
}

void lre::Initialize() {
	assert(lgl::IsInitialized());

	self->uniformbuffer = std::make_unique<lgl::UniformBuffer>();

	self->uniformbuffer->Bind();
	self->uniformbuffer->Allocate(sizeof(glm::mat4) * 4);
	self->uniformbuffer->BindRange(0, sizeof(glm::mat4) * 4, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));

	InitializeMainShaders();
}

void lre::InitializeMainShaders() {
	assert(lgl::IsInitialized());

	lgl::Shader screen_shader;
	screen_shader.VertexShader(SHADER_PATH("screen.vs"));
	screen_shader.FragmentShader(SHADER_PATH("regular_uv.fs"));
	screen_shader.Link();

	
}

void lre::SetFrameBuffer(lgl::FrameBuffer* framebuffer) {
	self->framebuffer = framebuffer;
}
void lre::SetShader(lgl::Shader* shader) {
	self->shader = shader;
}
void lre::SetVertexArray(lgl::VertexArray* vertexarray) {
	self->vertexarray = vertexarray;
}
void lre::SetVertexBuffer(lgl::VertexBuffer* vertexbuffer) {
	self->vertexbuffer = vertexbuffer;
}
void lre::SetIndexBuffer(lgl::IndexBuffer* indexbuffer) {
	self->indexbuffer = indexbuffer;
}

void lre::InsertShader(std::string name, lgl::Shader shader) {
	
}

lgl::Shader* lre::GetShader(std::string name) {
	if (self->shader_registry.find(name) == self->shader_registry.end())
		return nullptr;
	
	return &self->shader_registry[name];
}

