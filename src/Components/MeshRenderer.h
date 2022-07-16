#pragma once

#include <Structures/Structures.h>

namespace lucy {
	struct MeshRenderer {
		Mesh* mesh = nullptr;
		Material* material = nullptr;

		bool enable_lighting = false;

		MeshRenderer() {}
		MeshRenderer(Mesh* mesh): mesh(mesh) {}
		MeshRenderer(Mesh* mesh, Material* material): mesh(mesh), material(material) {}
	};
}