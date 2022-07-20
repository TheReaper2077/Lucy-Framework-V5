#pragma once

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <set>
#include <vector>

#include "Window.h"

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
		bool is_file_dropped = false;

		bool is_window_resized;

		void* payload_data = nullptr;
		std::string payload_type;

		bool drag_begin;

	public:
		void Init();
		void Update();

		bool IsKeyPressed(SDL_Scancode scancode);
		bool IsKeyPressedAny(SDL_Scancode scancode);
		bool IsKeyPressed(const std::vector<SDL_Scancode>& scancodes);
		bool IsKeyToggled(SDL_Scancode scancode);
		bool IsKeyChord(const std::vector<SDL_Scancode>& scancodes);

		bool IsQuittable();
		bool IsWindowResized();

		bool IsButtonPressed(unsigned int button);
		bool IsButtonPressedAny();
		bool IsButtonToggled(unsigned int button);

		const glm::vec3& GetCursorPos();
		const glm::vec3& GetCursorPosNormalized();
		const glm::vec3& GetCursorPosNormalized(Window* window);
		const glm::vec3& GetRelCursorPos();
		const glm::vec3& GetRelCursorPosNormalized();
		const glm::vec3& GetRelCursorPosNormalized(Window* window);
		const glm::vec3& GetRelCursorOffset();

		const std::string& GetDroppedFile();
		bool IsFileDropped();

		void SetPayload(void* data, const std::string& type);
		bool IsPayloadPresent();
		void* GetPayloadData();
		std::string GetPayloadType();

		SDL_Event& GetEvent();
	};
}