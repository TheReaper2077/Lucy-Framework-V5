#pragma once

#include <Engine/ECS.h>

namespace lucy {
	struct Panel {
		bool panel_open = true;
		std::string name;

		Registry& registry = Registry::Instance();

	public:
		Panel() {}
		Panel(std::string name): name(name) {}
		Panel(std::string name, bool open): name(name), panel_open(open) {}

	private:
		virtual void Render() = 0;

	public:
		void RenderWindow() {
			Render();
		}
	};
}