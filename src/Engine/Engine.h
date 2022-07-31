#pragma once

#include "ECS.h"
#include "Events.h"
#include "TimeStep.h"

namespace lucy {
	class Engine {
		SDL_Window* sdl_window = nullptr;
		SDL_GLContext sdl_glcontext;

		Registry& registry = Registry::Instance();

		typedef void(*system_func)(Registry&);

		std::vector<system_func> systems_array;
		std::vector<system_func> init_systems;

	public:
		void Init();
		void Mainloop();
		void Destroy();

		void AddRuntimeSystem(system_func func);
		void AddInitializationSystem(system_func func);

		SDL_Window* GetWindow() {
			return sdl_window;
		}
		SDL_GLContext* GetGLContext() {
			return &sdl_glcontext;
		}
	};
}