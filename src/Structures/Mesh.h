#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <array>
#include <vector>
#include <LucyRE/LucyRE.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lucy {
	struct Mesh {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec4> colors;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> uvw;

		std::vector<uint32_t> indices;

		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;
		lgl::VertexArray* vertexarray = nullptr;

		int vertexcount = 0;
		int indexcount = 0;

		lgl::Primitive primitive = lgl::TRIANGLE;

		bool enable_normal = true;
		bool enable_color = true;
		bool enable_uv = true;

		size_t flags;

		Mesh() {}
		~Mesh() {}

		Mesh(aiMesh* ai_mesh);

		void Import(aiMesh* ai_mesh);
		void Transfer();
		void RecalculateNormals();
		void ClearData();
	};
}