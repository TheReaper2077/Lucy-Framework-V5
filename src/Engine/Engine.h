#pragma once

#include "ECS.h"
#include "Events.h"
#include "TimeStep.h"

namespace lucy {
	class Engine {
		SDL_Window* sdl_window;
		SDL_GLContext sdl_context;

		Registry& registry = Registry::Instance();

	public:
		void Init();
		void Mainloop();
		void Destroy();
	};
}