#pragma once

#include <imgui.h>
#include <imgui_lucy_impl.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <Lucy/Lucy.h>

namespace lucy {
	class Editor {
		typedef void(*system_func)();
		std::vector<system_func> systems_array;

		#define self Instance()
		static Editor* Instance() {
			static Editor instance;
			return &instance;
		}

	public:
		Editor() {}
		~Editor() {}

		static void AddLayer(system_func func);

		static void Initialize();
		static void RenderBegin();
		static void RenderEnd();
		static void Update();
	};
}
