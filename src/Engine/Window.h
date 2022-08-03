#pragma once

#include <glm/vec2.hpp>
#include <LucyGL/LucyGL.h>
#include <string>
#include <SDL2/SDL.h>

namespace lucy {
	struct Window {
		glm::vec2 pos = { 50, 50 };
		glm::vec2 size = { 1366, 768 };

		std::string title = "Lucy Framework V5";
		lgl::FrameBuffer* framebuffer = nullptr;
		SDL_Window* sdl_window = nullptr;
		SDL_GLContext sdl_glcontext;

		Window() {}
		~Window() {
			Destroy();
		}

		void InitSDLWindow() {
			assert(sdl_window == nullptr);

			sdl_window = SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

			assert(sdl_window);

			sdl_glcontext = SDL_GL_CreateContext(sdl_window);
		}

		void InitSDLWindow(const char* title, int pos_x, int pos_y, int width, int height, uint32_t flags) {
			assert(sdl_window == nullptr);

			sdl_window = SDL_CreateWindow(title, pos_x, pos_y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | flags);

			assert(sdl_window);

			sdl_glcontext = SDL_GL_CreateContext(sdl_window);
			pos.x = pos_x;
			pos.y = pos_y;
			size.x = width;
			size.y = height;
			this->title = std::string(title);
		}

		void SwapWindow() {
			SDL_GL_SwapWindow(sdl_window);
		}

		void Destroy() {
			SDL_DestroyWindow(sdl_window);
		}
	};
}