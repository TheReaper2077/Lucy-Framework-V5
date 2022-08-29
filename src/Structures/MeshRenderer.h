#pragma once

#include <string>
#include "Mesh.h"
#include "Material.h"

namespace lucy {
	struct MeshRenderer {
		Mesh* mesh = nullptr;
		Material* material = nullptr;

		bool visible = true;
		bool enable_lighting = false;

		MeshRenderer() {}
	};
}