#include "WindowManager.h"

void lucy::WindowManager::Initialize() {
	Create(GAME_WINDOW);
	Create(EDITOR_WINDOW);
	Create(MAIN_WINDOW);
}

void lucy::WindowManager::Create(std::string name)  {
	assert(self->window_registry.find(name) == self->window_registry.end());

	self->window_registry[name] = Window{};
}

lucy::Window& lucy::WindowManager::Get(std::string name) {
	assert(self->window_registry.find(name) != self->window_registry.end());

	return self->window_registry[name];
}