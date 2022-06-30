#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

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