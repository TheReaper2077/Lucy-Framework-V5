#pragma once

#include <glm/glm.hpp>
#include <LucyGL/API.h>
#include <array>
#include <vector>
#include <Engine/TextureStore.h>

namespace lucy {
	struct Mesh {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec4> colors;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> uvw;

		std::vector<uint32_t> indices;

		TextureStore texture_store;

		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;
		lgl::VertexArray* vertexarray = nullptr;

		int vertexcount = 0;
		int indexcount = 0;

		lgl::Primitive primitive = lgl::TRIANGLE;

		bool disable_position = false;
		bool disable_normal = false;
		bool disable_color = false;
		bool disable_uv = false;

		size_t flags;

		void Transfer();
		void ReCalculateNormals();
		void Clear();
	};
}