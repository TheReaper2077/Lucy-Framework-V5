#pragma once

#include "Mesh.h"

namespace lucy {
	struct MeshBuilder {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec4> colors;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> uvw;

		std::vector<uint32_t> indices;

		bool enable_normal = true;
		bool enable_color = true;
		bool enable_uv = true;

		size_t flags;

		Mesh* mesh = nullptr;

		lgl::Primitive primitive;

		void Import(aiMesh* ai_mesh);
		void Transfer();
		void RecalculateNormals();
		void ClearData();
	};
}