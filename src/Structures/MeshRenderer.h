#pragma once

#include "Component.h"
#include <string>

namespace lucy {
	struct MeshRenderer: public ComponentTemplate {
		std::string mesh_id;
		std::string material_id;

		bool visible = true;
		bool enable_lighting = false;

		MeshRenderer() {}

		void ImGuiRender() override;
	};
}