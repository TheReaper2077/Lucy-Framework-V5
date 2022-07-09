#pragma once

#include "Mesh.h"

namespace lucy::Components {
	struct MeshRenderer {
		Mesh* mesh = nullptr;
	};
}