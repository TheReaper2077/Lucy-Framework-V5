#pragma once

#include <glm/glm.hpp>
#include <tuple>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

namespace util {
	typedef glm::vec3 position_array;
	typedef glm::vec3 normal_array;
	typedef glm::vec4 color_array;
	typedef glm::vec2 uv_array;
	typedef glm::vec3 uvw_array;

	typedef color_array* color_2d_array;
	typedef uv_array* uv_2d_array;
	typedef uvw_array* uvw_2d_array;

	// auto [vertexcount, positions, normals, colors, uvs, uvws, indexcount, indices]
	typedef std::tuple<int, position_array*, normal_array*, color_2d_array*, uv_2d_array*, uvw_2d_array*, int, uint32_t*> TYPE_MESH;

	// // auto [vertexcount, positions, normals, colors, uvs, uvws, indexcount, indices]
	// typedef std::tuple<int, position_array*, normal_array*, col_2d_array*, uv_2d_array*, uvw_2d_array*, int, uint32_t*> TYPE_MATERIAL;

	TYPE_MESH LoadMesh(const std::string& filename, const std::string& mesh_name);
	std::vector<std::pair<std::string, TYPE_MESH>> LoadMeshAll(const std::string& filename);

	void Free(TYPE_MESH& mesh);
}
