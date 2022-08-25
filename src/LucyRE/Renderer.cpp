#include "Renderer.h"
#include "DrawList.h"
#include "Vertex.h"

void lre::Renderer::SetModel(const glm::mat4& model) {
	if (self->model == model) return;
	self->model = model;
	self->uniformbuffer->AddDataDynamic(&self->model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}

void lre::Renderer::SetView(const glm::mat4& view) {
	if (self->view == view) return;
	self->view = view;
	self->uniformbuffer->AddDataDynamic(&self->view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}

void lre::Renderer::SetProjection(const glm::mat4& projection) {
	if (self->projection == projection) return;
	self->projection = projection;
	self->uniformbuffer->AddDataDynamic(&self->projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}

void lre::Renderer::SetViewPosition(const glm::vec3& view_position) {
	if (self->view_position == view_position) return;
	self->view_position = view_position;
	self->uniformbuffer->AddDataDynamic(&self->view_position[0], sizeof(glm::vec3), sizeof(glm::mat4) * 3);
}

void lre::Renderer::Initialize() {
	self->uniformbuffer = std::make_unique<lgl::UniformBuffer>();

	self->uniformbuffer->Bind();
	self->uniformbuffer->Allocate(sizeof(glm::mat4) * 4);
	self->uniformbuffer->BindRange(0, sizeof(glm::mat4) * 4, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));
}

void lre::Renderer::SetFrameBuffer(lgl::FrameBuffer* framebuffer) {
	self->framebuffer = framebuffer;
}
void lre::Renderer::SetShader(lgl::Shader* shader) {
	self->shader = shader;
}
void lre::Renderer::SetVertexArray(lgl::VertexArray* vertexarray) {
	self->vertexarray = vertexarray;
}
void lre::Renderer::SetVertexBuffer(lgl::VertexBuffer* vertexbuffer) {
	self->vertexbuffer = vertexbuffer;
}
void lre::Renderer::SetIndexBuffer(lgl::IndexBuffer* indexbuffer) {
	self->indexbuffer = indexbuffer;
}

