#pragma once

#include <LucyGL/LucyGL.h>
#include <memory>
#include <Engine/Window.h>
#include <string>

namespace lucy {
	struct WindowRegistry {
		std::unordered_map<std::string, std::shared_ptr<Window>> window_registry;

		WindowRegistry();
		Window* operator[](const std::string& name);
		Window* Create(const std::string& name);
	};
}