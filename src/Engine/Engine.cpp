#include "Engine.h"
#include "Window.h"

#include "Renderer.h"

#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>

void lucy::Engine::Init() {
	auto null_entity = registry.create();

	auto& window = registry.store<Window>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	sdl_window = SDL_CreateWindow(window.title.c_str(), window.pos.x, window.pos.y, window.size.x, window.size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(sdl_window);

	sdl_context = SDL_GL_CreateContext(sdl_window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
}

void lucy::Engine::Mainloop() {
	auto& timestep = registry.store<TimeStep>();
	auto& events = registry.store<Events>();
	auto& window = registry.store<Window>();
	auto& renderer = registry.store<Renderer>();

	auto* texture = new lgl::Texture();
	texture->Bind();
	texture->LoadFile("D:\\C++\\Lucy Framework V4\\assets\\Gold.PNG");

	texture->BindUnit(1);

	renderer.SetOrtho(0, window.size.x, window.size.y, 0, -1, 1);

	auto* shader = renderer.shaderregistry.GetShader(ShaderFlag::TEXTUREID);
	shader->Bind();

	lgl::VertexBuffer* vertexbuffer = new lgl::VertexBuffer();

	using Vertex = lucy::Vertex::P1UV1T1;

	std::vector<Vertex> vertices;
	auto* vertexarray = Vertex::VertexArray();

	Primitives::QuadIndexed(vertices, { 100, 100, 0 }, { 100, 100 }, { 0, 0 }, { 1, 1 }, 1);
	Primitives::QuadIndexed(vertices, { 300, 300, 0 }, { 100, 100 }, { 0, 0 }, { 1, 1 }, 1);

	vertexbuffer->Bind();
	vertexbuffer->Allocate(sizeof(decltype(vertices[0]))*vertices.size());
	vertexbuffer->AddDataDynamic(vertices.data(), sizeof(decltype(vertices[0]))*vertices.size());

	while (!events.IsQuittable()) {
		events.Update();
		timestep.Update();

		if (events.IsWindowResized()) {
			window.pos = events.GetWindowPos();
			window.size = events.GetWindowSize();
		}

		shader->Bind();
		vertexarray->Bind();
		vertexarray->BindIndexBuffer(Primitives::GetQuadIndices(vertices.size()));
		vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);

		lgl::DrawIndexed(lgl::TRIANGLE, vertices.size()*1.5, lgl::UNSIGNED_INT, nullptr);

		SDL_GL_SwapWindow(sdl_window);
	}
}

void lucy::Engine::Destroy() {
	SDL_DestroyWindow(sdl_window);
}
