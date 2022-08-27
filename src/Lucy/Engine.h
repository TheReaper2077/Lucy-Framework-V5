#pragma once

#include "ECS.h"
#include "Events.h"
#include "TimeStep.h"

namespace lucy {
	class Engine {
		typedef void(*system_func)();

		std::vector<system_func> systems_array;
		std::vector<system_func> init_systems;

		#define self Instance()

		static Engine* Instance() {
			static Engine instance;
			return &instance;
		}

	public:
		static void Initialize();
		static void Mainloop();
		static void Destroy();

		static void AddRuntimeSystem(system_func func);
		static void AddInitializationSystem(system_func func);
	};
}