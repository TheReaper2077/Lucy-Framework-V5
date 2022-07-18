#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <Engine/ECS.h>
#include <Registry/Registry.h>

namespace lucy {
	class Editor {
	public:
		Editor() {}

		void Init(SDL_Window* sdl_window, SDL_GLContext* sdl_glcontext);
		void Render();
	};
}