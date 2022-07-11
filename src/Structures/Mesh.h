#pragma once

#include <glm/glm.hpp>
#include <LucyGL/API.h>
#include <array>
#include <vector>
#include <Engine/TextureStore.h>

namespace lucy {
	struct Mesh {
		std::vector<glm::vec3> position;
		std::vector<glm::vec3> normal;
		std::vector<glm::vec4> color;
		std::vector<glm::vec2> uv;

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
	};
}