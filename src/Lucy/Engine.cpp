#include "Engine.h"
#include "Window.h"

#include <Structures/Structures.h>

#include "State.h"
#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include <LucyRE/LucyRE.h>
#include "WindowManager.h"
#include "AssetLoader.h"

static auto& registry = lucy::Registry::Instance();

void lucy::Engine::Initialize() {
	auto null_entity = registry.create();
	auto& state = registry.store<State>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	registry.store<Window>().InitSDLWindow();

	lgl::Initialize(SDL_GL_GetProcAddress);
	lre::Initialize();
	AssetLoader::Initialize();

	state.render_to_screen = true;
}

void lucy::Engine::Mainloop() {
	for (auto system_func: self->init_systems) {
		system_func();
	}

	while (!Events::IsQuittable()) {
		auto& state = registry.store<State>();

		const auto& start_time = std::chrono::high_resolution_clock::now();

		Events::Update();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// glDepthFunc(GL_LEQUAL);

		static double count = 0;
		static int fps = 0;

		if (count >= 60) {
			state.fps = fps;
			count = 0;
			fps = 0;
		}

		fps++;
		count += TimeStep::dt;

		for (auto system_func: self->systems_array) {
			system_func();
		}

		registry.store<Window>().SwapWindow();

		if (Events::IsKeyChord({ SDL_SCANCODE_LALT, SDL_SCANCODE_F4 })) {
			Events::IsQuittable() = true;
		}

		const auto& end_time = std::chrono::high_resolution_clock::now();
		TimeStep::dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
	}
}

void lucy::Engine::ShutDown() {
	lre::Destroy();
	registry.store<Window>().Destroy();
	registry.clear();

	// SDL_Quit();
}


void lucy::Engine::AddRuntimeSystem(system_func func) {
	for (auto fn: self->systems_array)
		assert(func != fn);

	self->systems_array.push_back(func);
}

void lucy::Engine::AddInitializationSystem(system_func func) {
	for (auto fn: self->init_systems)
		assert(func != fn);

	self->init_systems.push_back(func);
}
