#include "Events.h"

void lucy::Events::Update() {
	while (SDL_PollEvent(&event)) {
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
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			pressed_buttons.erase(event.button.button);
		}
		if (event.type == SDL_MOUSEWHEEL) {
			scrollup = (event.wheel.y > 0);
			scrolldown = (event.wheel.y < 0);
		}
		if (event.type == SDL_DROPFILE) {
			dropfilename = std::string(event.drop.file);
		}
	}
}

void lucy::Events::SetWindowPos(const glm::vec2& pos) {
	window_pos = pos;
}

void lucy::Events::SetWindowSize(const glm::vec2& size) {
	window_size = size;
}

const glm::vec2& lucy::Events::GetWindowPos() {
	return window_pos;
}

const glm::vec2& lucy::Events::GetWindowSize() {
	return window_size;
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

bool lucy::Events::IsButtonToggled(unsigned int button) {
	return toggled_buttons.contains(button);
}

const glm::vec3& lucy::Events::GetCursorPos() {
	return mousepos;
}

const glm::vec3& lucy::Events::GetCursorPosNormalized() {
	return glm::vec3 {
		mousepos.x - window_pos.x / (window_size.x * 0.5) - 1.0,
		1.0 - ((mousepos.y - window_pos.y) / (window_size.y * 0.5)),
		0
	};
}

const glm::vec3& lucy::Events::GetRelCursorPos() {
	return relmousepos;
}

const glm::vec3& lucy::Events::GetRelCursorPosNormalized() {
	return glm::vec3 {
		relmousepos.x - window_pos.x / (window_size.x * 0.5) - 1.0,
		1.0 - ((relmousepos.y - window_pos.y) / (window_size.y * 0.5)),
		0
	};
}

const glm::vec3& lucy::Events::GetRelCursorOffset() {
	return relmouseoffset;
}

const std::string& lucy::Events::GetDroppedFile() {
	return dropfilename;
}
