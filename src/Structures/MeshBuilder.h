#pragma once

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <LucyUtil/LucyUtil.h>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lucy {
	struct MeshBuilder {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec4> color[8];
		std::vector<glm::vec2> uv[8];
		std::vector<glm::vec3> uvw[8];

		std::vector<uint32_t> indices;

		lgl::Primitive primitive = lgl::TRIANGLE;

		Mesh* mesh = nullptr;

		void Load(std::string filename, std::string mesh_name);
		void Load(const util::TYPE_MESH& mesh);
		void Build();
	};
}