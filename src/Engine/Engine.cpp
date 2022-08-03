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
#include "Scene.h"

void lucy::Engine::Init() {
	auto null_entity = registry.create();
	auto& events = registry.store<Events>();
	auto& meshregistry = registry.store<MeshRegistry>();
	auto& window = registry.store<Window>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window.InitSDLWindow();

	lgl::Initialize(SDL_GL_GetProcAddress);
	lre::Initialize();
}

void lucy::Engine::Mainloop() {
	auto& events = registry.store<Events>();
	auto& timestep = registry.store<TimeStep>();
	auto& window = registry.store<Window>();

	for (auto system_func: init_systems) {
		system_func(registry);
	}

	while (!events.IsQuittable()) {
		const auto& start_time = std::chrono::high_resolution_clock::now();

		events.Update();
		timestep.Update();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);

		if (timestep.dt < 1) {
			for (auto system_func: systems_array) {
				system_func(registry);
			}
		}

		window.SwapWindow();

		const auto& end_time = std::chrono::high_resolution_clock::now();
		timestep.dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
	}
}

void lucy::Engine::Destroy() {
	
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
