#include "Engine.h"
#include "Window.h"

#include <Registry/Registry.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <Structures/Structures.h>
#include <System/System.h>

#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>

void lucy::Engine::Init() {
	auto null_entity = registry.create();
	auto& renderer = registry.store<Renderer>();
	auto& events = registry.store<Events>();
	auto& meshregistry = registry.store<MeshRegistry>();
	auto& window = registry.store<Window>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	sdl_window = SDL_CreateWindow(window.title.c_str(), window.pos.x, window.pos.y, window.size.x, window.size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(sdl_window);

	sdl_glcontext = SDL_GL_CreateContext(sdl_window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	events.Init();
	renderer.Init();
	meshregistry.Init();
}

void lucy::Engine::Mainloop() {
	auto& events = registry.store<Events>();
	auto& timestep = registry.store<TimeStep>();

	for (auto system_func: init_systems) {
		system_func(registry);
	}

	while (!events.IsQuittable()) {
		events.Update();
		timestep.Update();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);

		for (auto system_func: systems_array) {
			system_func(registry);
		}

		SDL_GL_SwapWindow(sdl_window);
	}
}

void lucy::Engine::Destroy() {
	SDL_DestroyWindow(sdl_window);
}

void lucy::Engine::AddRuntimeSystem(system_func func) {
	for (auto fn: systems_array)
		assert(func != fn);

	systems_array.push_back(func);
}

void lucy::Engine::AddInitializationSystem(system_func func) {
	for (auto fn: init_systems)
		assert(func != fn);

	init_systems.push_back(func);
}
