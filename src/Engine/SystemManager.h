#pragma once

namespace lucy {
	struct SystemRegistry {
		void AddSystem();
		void SystemIterate();
		template <typename T, typename ...Args>
		void RunSystem() {
			
		}
	};
}