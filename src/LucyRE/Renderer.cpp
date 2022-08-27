#include "Renderer.h"
#include "DrawList.h"
#include "Vertex.h"
#include <iostream>

#define self lre::Renderer::Instance()

#include <filesystem>

// #define SHADER_PATH(rel_filepath) std::filesystem::current_path().string() + "\\Shaders\\" + std::string(rel_filepath)
#define SHADER_PATH(rel_filepath) "D:\\C++\\Lucy Framework V5\\src\\LucyRE\\Shaders\\" + std::string(rel_filepath)

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

void lre::Clear(const glm::vec4& clearcolor, uint32_t flags) {
	lgl::ClearColor(clearcolor.x, clearcolor.y, clearcolor.z, clearcolor.w);
	lgl::Clear(flags);
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

	lgl::Shader* screen = new lgl::Shader();
	screen->VertexShader(SHADER_PATH("screen.vs"));
	screen->FragmentShader(SHADER_PATH("uv.fs"));
	screen->Link();
	self->shader_registry["screen"] = screen;

	lgl::Shader* const_color = new lgl::Shader();
	const_color->VertexShader(SHADER_PATH("vertex.vs"));
	const_color->FragmentShader(SHADER_PATH("const_color.fs"));
	const_color->Link();
	self->shader_registry["const_color"] = const_color;

	lgl::Shader* color = new lgl::Shader();
	color->VertexShader(SHADER_PATH("vertex.vs"));
	color->FragmentShader(SHADER_PATH("color.fs"));
	color->Link();
	self->shader_registry["color"] = color;

	lgl::Shader* normal = new lgl::Shader();
	normal->VertexShader(SHADER_PATH("vertex.vs"));
	normal->FragmentShader(SHADER_PATH("normal.fs"));
	normal->Link();
	self->shader_registry["normal"] = normal;

	lgl::Shader* uv = new lgl::Shader();
	uv->VertexShader(SHADER_PATH("vertex.vs"));
	uv->FragmentShader(SHADER_PATH("uv.fs"));
	uv->Link();
	self->shader_registry["uv"] = uv;

	lgl::Shader* uvw = new lgl::Shader();
	uvw->VertexShader(SHADER_PATH("vertex.vs"));
	uvw->FragmentShader(SHADER_PATH("uvw.fs"));
	uvw->Link();
	self->shader_registry["uvw"] = uvw;
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

void lre::InsertShader(std::string name, lgl::Shader* shader) {
	assert(self->shader_registry.find(name) == self->shader_registry.end());

	self->shader_registry[name] = shader;
}

lgl::Shader* lre::GetShader(std::string name) {
	if (self->shader_registry.find(name) == self->shader_registry.end())
		return nullptr;
	
	return self->shader_registry[name];
}

void lre::Destroy() {
	for (auto& pair: self->shader_registry) {
		free(pair.second);
	}
}

