#pragma once

#include <Engine/ECS.h>

namespace lucy {
	enum PanelInstance_ {
		PanelInstance_None,
		PanelInstance_Game,
		PanelInstance_Editor,
		PanelInstance_Inspector,
		PanelInstance_SceneHeirarchy,

		PanelInstance_COUNT,
	};

	struct PanelTemplate {
	protected:
		bool panel_open = true;
		std::string name;

		Registry& registry = Registry::Instance();

	public:
		virtual void Render() = 0;
	};

	template <unsigned int T>
	struct Panel: public PanelTemplate {
	public:
		Panel() {}
		Panel(std::string name): name(name) {}
		Panel(std::string name, bool open): name(name), panel_open(open) {}
	
		void Render() override;
	};
}