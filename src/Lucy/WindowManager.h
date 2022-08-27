#pragma once

#include <unordered_map>
#include "Window.h"

namespace lucy {
	#define MAIN_WINDOW "---MAIN_WINDOW-LUCY_000---"
	#define GAME_WINDOW "---GAME_WINDOW-LUCY_001---"
	#define EDITOR_WINDOW "---EDITOR_WINDOW-LUCY_002---"

	class WindowManager {
		std::unordered_map<std::string, Window> window_registry;

		static WindowManager* Instance() {
			static WindowManager instance;
			return &instance;
		}

		#define self Instance()
		
	public:
		static void Initialize();
		
		static void Create(std::string name);
		static Window& Get(std::string name);
	};
}