#pragma once

#include "ECS.h"
#include "Events.h"
#include "TimeStep.h"

namespace lucy {
	class Engine {
		SDL_Window* sdl_window = nullptr;
		SDL_GLContext sdl_glcontext;

		Registry& registry = Registry::Instance();

	public:
		void Init();
		void Mainloop();
		void Destroy();

		SDL_Window* GetWindow() {
			return sdl_window;
		}
		SDL_GLContext* GetGLContext() {
			return &sdl_glcontext;
		}
	};
}