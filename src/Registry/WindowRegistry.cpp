#include "Registry.h"
#include <Engine/ECS.h>
#include <Engine/Events.h>

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>

static auto& registry = lucy::Registry::Instance();

lucy::WindowRegistry::WindowRegistry() {
	Create(MAIN_WINDOW);
	Create(GAME_WINDOW);
	Create(EDITOR_WINDOW);
	Create(SANDBOX_WINDOW);
}

lucy::Window* lucy::WindowRegistry::operator[](const std::string& name) {
	if (window_registry.find(name) == window_registry.end()) {
		return nullptr;
	}

	return window_registry[name].get();
}

lucy::Window* lucy::WindowRegistry::Create(const std::string& name) {
	window_registry[name] = std::make_shared<Window>();

	return window_registry[name].get();
}
