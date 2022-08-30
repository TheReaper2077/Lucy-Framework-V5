#pragma once

#include "Mesh.h"
#include "Material.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lucy {
	struct Model {
		std::vector<Mesh*> meshes;
		std::vector<Material*> materials;

		std::map<Mesh*, Material*> mesh_material_link;

		Model() {}
	};
}