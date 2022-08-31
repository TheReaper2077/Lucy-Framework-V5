#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lucy {
	struct Material {
		glm::vec3 ambient = { 1.0, 0.5, 0.31 };
		glm::vec3 diffuse = { 1.0, 0.5, 0.31 };
		glm::vec3 specular = { 0.5, 0.5, 0.5 };
		float shininess = 32;

		Material() {}
		Material(aiMaterial* ai_material);
	};
}