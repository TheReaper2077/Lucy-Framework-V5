#pragma once

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lucy {
	struct MeshBuilder {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec4> color;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> uvw;

		std::vector<uint32_t> indices;

		lgl::Primitive primitive = lgl::TRIANGLE;

		void Initialize(aiMesh* ai_mesh);
	};
}