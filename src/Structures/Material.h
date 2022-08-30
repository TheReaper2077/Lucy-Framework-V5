#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lucy {
	struct Material {
		

		Material() {}
		Material(aiMaterial* ai_material);
	};
}