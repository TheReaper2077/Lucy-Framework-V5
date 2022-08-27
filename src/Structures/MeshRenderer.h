#pragma once

#include <string>

namespace lucy {
	struct MeshRenderer {
		std::string mesh_id;
		std::string material_id;

		bool visible = true;
		bool enable_lighting = false;

		MeshRenderer() {}
	};
}