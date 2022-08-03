#include "Events.h"
#include <imgui_impl_sdl.h>
#include "ECS.h"
#include "Window.h"
#include <iostream>

static auto& registry = lucy::Registry::Instance();

void lucy::Events::Init() {
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
}

void lucy::Events::Update() {
	if (!is_init) {
		Init();
		is_init = true;
	}

	is_file_dropped = false;

	dropfilename = "";
	drag_begin = false;
	static bool drag_end;
	static int drag_count;

	if (drag_count > 1) {
		payload_data = nullptr;
		payload_type = "";
		drag_end = false;
	}

	if (drag_end) {
		drag_count++;
	} else {
		drag_count = 0;
	}

	while (SDL_PollEvent(&event)) {
		// ImGui_ImplSDL2_ProcessEvent(&event);

		is_quit = (event.type == SDL_QUIT);

		if (event.type == SDL_MOUSEMOTION) {
			relmousepos.x += event.motion.xrel;
			relmousepos.y += event.motion.yrel;
			
			relmouseoffset.x = event.motion.xrel;
			relmouseoffset.y = event.motion.yrel;

			mousepos.x = event.motion.x;
			mousepos.y = event.motion.y;
		}
		if (event.type == SDL_KEYDOWN) {
			pressed_keys.insert(event.key.keysym.scancode);
			if (key_chord.size() == 0)
				key_chord.push_back(event.key.keysym.scancode);
			else if (key_chord.back() != event.key.keysym.scancode)
				key_chord.push_back(event.key.keysym.scancode);
		}
		if (event.type == SDL_KEYUP) {
			if (pressed_keys.count(event.key.keysym.scancode)) {
				if (!toggled_keys.contains(event.key.keysym.scancode))
					toggled_keys.insert(event.key.keysym.scancode);
				else
					toggled_keys.erase(event.key.keysym.scancode);
			}
			key_chord.clear();
			pressed_keys.erase(event.key.keysym.scancode);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			pressed_buttons.insert(event.button.button);
			if (event.button.button == SDL_BUTTON_LEFT) {
				drag_begin = true;
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			pressed_buttons.erase(event.button.button);
			if (event.button.button == SDL_BUTTON_LEFT) {
				drag_end = true;
			}
		}
		if (event.type == SDL_MOUSEWHEEL) {
			scrollup = (event.wheel.y > 0);
			scrolldown = (event.wheel.y < 0);
		}
		if (event.type == SDL_DROPFILE) {
			dropfilename = std::string(event.drop.file);
			is_file_dropped = true;
		}
	}
}

bool lucy::Events::IsKeyPressed(SDL_Scancode scancode) {
	return pressed_keys.contains(scancode);
}

bool lucy::Events::IsKeyPressed(const std::vector<SDL_Scancode>& scancodes) {
	for (int i = 0; i < scancodes.size(); i++) {
		if (!pressed_keys.contains(scancodes[i]))
			return false;
	}

	return true;
}

bool lucy::Events::IsKeyToggled(SDL_Scancode scancode) {
	return toggled_keys.contains(scancode);
}

bool lucy::Events::IsKeyChord(const std::vector<SDL_Scancode>& key_chord) {
	if (key_chord.size() < this->key_chord.size()) return false;

	for (int i = 0; i < key_chord.size(); i++) {
		if (key_chord[i] != this->key_chord[i])
			return false;
	}

	return true;
}

bool lucy::Events::IsQuittable() {
	return is_quit;
}

bool lucy::Events::IsWindowResized() {
	return is_window_resized;
}

bool lucy::Events::IsButtonPressed(unsigned int button) {
	return (pressed_buttons.contains(button));
}

bool lucy::Events::IsButtonPressedAny() {
	return (pressed_buttons.size() > 0);
}

bool lucy::Events::IsButtonToggled(unsigned int button) {
	return toggled_buttons.contains(button);
}

const glm::vec3& lucy::Events::GetCursorPosNormalized() {
	return GetCursorPosNormalized(&registry.store<Window>());
}

const glm::vec3& lucy::Events::GetCursorPos() {
	return mousepos;
}

const glm::vec3& lucy::Events::GetCursorPosNormalized(Window* window) {
	assert(window);

	return glm::vec3 {
		mousepos.x - window->pos.x / (window->size.x * 0.5) - 1.0,
		1.0 - ((mousepos.y - window->pos.y) / (window->size.y * 0.5)),
		0
	};
}

const glm::vec3& lucy::Events::GetRelCursorPosNormalized() {
	return GetRelCursorPosNormalized(&registry.store<Window>());
}

const glm::vec3& lucy::Events::GetRelCursorPos() {
	return relmousepos;
}

const glm::vec3& lucy::Events::GetRelCursorPosNormalized(Window* window) {
	assert(window);

	return glm::vec3 {
		relmousepos.x - window->pos.x / (window->size.x * 0.5) - 1.0,
		1.0 - ((relmousepos.y - window->pos.y) / (window->size.y * 0.5)),
		0
	};
}

const glm::vec3& lucy::Events::GetRelCursorOffset() {
	return relmouseoffset;
}

const std::string& lucy::Events::GetDroppedFile() {
	return dropfilename;
}

bool lucy::Events::IsFileDropped() {
	return is_file_dropped;
}

void lucy::Events::SetPayload(void* data, const std::string& type) {
	payload_data = data;
	payload_type = type;
}

bool lucy::Events::IsPayloadPresent() {
	return (payload_data != nullptr);
}

void* lucy::Events::GetPayloadData() {
	return payload_data;
}

std::string lucy::Events::GetPayloadType() {
	return payload_type;
}

SDL_Event& lucy::Events::GetEvent() {
	return event;
}
