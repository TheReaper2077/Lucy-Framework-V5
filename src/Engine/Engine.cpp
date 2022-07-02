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

	auto* texture_2 = new lgl::Texture();
	texture_2->Bind();
	texture_2->LoadFile(nullptr);

	renderer.SetOrtho(0, window.size.x, window.size.y, 0, -1, 1);

	lgl::VertexBuffer* vertexbuffer = new lgl::VertexBuffer();

	using Vertex = lucy::Vertex::P1UV1T1;

	std::vector<Vertex> vertices;
	auto* vertexarray = Vertex::VertexArray();

	texture->UnBind();

	Primitives::QuadIndexed(vertices, { 100, 100, 0 }, { 100, 100 }, { 0, 0 }, { 1, 1 }, 0);
	Primitives::QuadIndexed(vertices, { 300, 300, 0 }, { 100, 100 }, { 0, 0 }, { 1, 1 }, 1);
	Primitives::QuadIndexed(vertices, { 500, 100, 0 }, { 100, 100 }, { 0, 0 }, { 1, 1 }, 0);

	vertexbuffer->Bind();
	vertexbuffer->Allocate(sizeof(decltype(vertices[0]))*vertices.size());
	vertexbuffer->AddDataDynamic(vertices.data(), sizeof(decltype(vertices[0]))*vertices.size());

	texture->BindUnit(0);
	texture_2->BindUnit(1);

	while (!events.IsQuittable()) {
		events.Update();

		timestep.Update();

		if (events.IsWindowResized()) {
			window.pos = events.GetWindowPos();
			window.size = events.GetWindowSize();
		}

		renderer.RenderTextureIdQuads(vertexarray, vertexbuffer, vertices.size());

		SDL_GL_SwapWindow(sdl_window);
	}
}

void lucy::Engine::Destroy() {
	SDL_DestroyWindow(sdl_window);
}
