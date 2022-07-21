#pragma once

#include <Engine/ECS.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include "Gui.h"

namespace lucy {
	enum PanelInstance_ {
		PanelInstance_None,
		PanelInstance_Game,
		PanelInstance_Editor,
		PanelInstance_Inspector,
		PanelInstance_SceneHeirarchy,

		PanelInstance_MaterialEditor,
		PanelInstance_MaterialViewer,
		PanelInstance_MaterialRegistry,

		PanelInstance_MeshViewer,
		PanelInstance_MeshRegistry,

		PanelInstance_SpriteEditor,
		PanelInstance_SpriteRegistry,

		PanelInstance_TextureEditor,
		PanelInstance_TextureRegistry,

		PanelInstance_Statistics,

		PanelInstance_Explorer,

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