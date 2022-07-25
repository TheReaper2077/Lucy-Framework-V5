#pragma once

#include <glm/vec2.hpp>
#include <LucyGL/LucyGL.h>
#include <string>

namespace lucy {
	#define MAIN_WINDOW "main_window"
	#define GAME_WINDOW "game_window"
	#define EDITOR_WINDOW "editor_window"
	#define SANDBOX_WINDOW "sandbox_window"

	struct Window {
		glm::vec2 pos = { 50, 50 };
		glm::vec2 size = { 1366, 768 };

		std::string title = "Lucy Framework V5";
		lgl::FrameBuffer* framebuffer = nullptr;

		Window() {}
		~Window() {}
	};
}