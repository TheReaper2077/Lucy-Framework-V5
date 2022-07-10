#pragma once

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <set>
#include <vector>

namespace lucy {
	class Events {
		bool is_quit;

		SDL_Event event;

		std::set<SDL_Scancode> pressed_keys;
		std::set<SDL_Scancode> toggled_keys;
		std::vector<SDL_Scancode> key_chord;

		std::set<unsigned int> pressed_buttons;
		std::set<unsigned int> toggled_buttons;
		glm::vec3 mousepos;
		glm::vec3 relmousepos;
		glm::vec3 relmouseoffset;

		bool scrollup;
		bool scrolldown;

		std::string dropfilename;

		glm::vec2 window_pos;
		glm::vec2 window_size;

		bool is_window_resized;

	public:
		void Update();

		void SetWindowPos(const glm::vec2& pos);
		void SetWindowSize(const glm::vec2& size);
		const glm::vec2& GetWindowPos();
		const glm::vec2& GetWindowSize();

		bool IsKeyPressed(SDL_Scancode scancode);
		bool IsKeyPressed(const std::vector<SDL_Scancode>& scancodes);
		bool IsKeyToggled(SDL_Scancode scancode);
		bool IsKeyChord(const std::vector<SDL_Scancode>& scancodes);

		bool IsQuittable();
		bool IsWindowResized();

		bool IsButtonPressed(unsigned int button);
		bool IsButtonToggled(unsigned int button);

		const glm::vec3& GetCursorPos();
		const glm::vec3& GetCursorPosNormalized();
		const glm::vec3& GetRelCursorPos();
		const glm::vec3& GetRelCursorPosNormalized();
		const glm::vec3& GetRelCursorOffset();

		const std::string& GetDroppedFile();		
	};
}