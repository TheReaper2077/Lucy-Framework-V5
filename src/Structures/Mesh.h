#pragma once

#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>
#include <LucyUtil/LucyUtil.h>

namespace lucy {
	struct Mesh {
		lgl::VertexArray* vertexarray = nullptr;
		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;

		int vertexcount = 0;
		int indexcount = 0;

		lgl::Primitive primitive = lgl::TRIANGLE;

		Mesh() {}
		~Mesh();

		void Load(const std::string& filename, const std::string& mesh_name);
		void Load(const util::TYPE_MESH& mesh);

		void Load(const std::string& filename, const std::string& mesh_name, const glm::vec3& offset, bool reconstruct_normals = false);
		void Load(const util::TYPE_MESH& mesh, const glm::vec3& offset, bool reconstruct_normals = false);

		void Load(const int vertexcount = 0, const util::position_array* positions = nullptr, const util::normal_array* normals = nullptr, const util::color_array* color = nullptr, const util::uv_array* uv = nullptr, const util::uvw_array* uvw = nullptr, const int indexcount = 0, const uint32_t* indices = nullptr, const glm::vec3& offset = { 0, 0, 0 });
	};
}