#include "Mesh.h"
#include <LucyRE/LucyRE.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

lucy::Mesh::~Mesh() {
	delete vertexbuffer;
	delete indexbuffer;
}

void RecalculateNormals(int vertexcount, util::position_array* positions, util::normal_array* normals, int indexcount, uint32_t* indices) {
	if (positions == nullptr) return;
	if (normals == nullptr)
		normals = new util::normal_array[vertexcount];

	if (indices == nullptr && indexcount == 0) {
		for (int i = 0; i < indexcount / 3; i++) {
			auto A = positions[indices[i * 3 + 0]];
			auto B = positions[indices[i * 3 + 1]];
			auto C = positions[indices[i * 3 + 2]];

			auto normal = glm::normalize(glm::cross((B - A), (C - A)));

			normals[indices[i * 3 + 0]] = normal;
			normals[indices[i * 3 + 0]] = normal;
			normals[indices[i * 3 + 0]] = normal;
		}

		return;
	}
	for (int i = 0; i < vertexcount / 3; i++) {
		auto A = positions[i * 3 + 0];
		auto B = positions[i * 3 + 1];
		auto C = positions[i * 3 + 2];

		auto normal = glm::normalize(glm::cross((B - A), (C - A)));

		normals[i * 3 + 0] = normal;
		normals[i * 3 + 1] = normal;
		normals[i * 3 + 2] = normal;
	}
}

const glm::vec3& FindCenter(int vertexcount, util::position_array* positions) {
	glm::vec3 center = { 0, 0, 0 };

	for (int i = 0; i < vertexcount; i++)
		center += positions[i];

	center /= vertexcount;

	return center;
}

void lucy::Mesh::Load(const std::string& filename, const std::string& mesh_name, const glm::vec3& offset, bool reconstruct_normals) {
	auto mesh = util::LoadMesh(filename, mesh_name);

	Load(mesh, offset, reconstruct_normals);

	util::Free(mesh);
}

void lucy::Mesh::Load(const util::TYPE_MESH& mesh, const glm::vec3& offset, bool reconstruct_normals) {
	const auto& [vertexcount, positions, normals, colors, uvs, uvws, indexcount, indices] = mesh;

	if (reconstruct_normals)
		RecalculateNormals(vertexcount, positions, normals, indexcount, indices);

	Load(vertexcount, positions, normals, (colors != nullptr) ? colors[0]: nullptr, (uvs != nullptr) ? uvs[0]: nullptr, (uvws != nullptr) ? uvws[0]: nullptr, indexcount, indices, offset);
}

void lucy::Mesh::Load(const std::string& filename, const std::string& mesh_name) {
	auto mesh = util::LoadMesh(filename, mesh_name);

	Load(mesh);

	util::Free(mesh);
}

void lucy::Mesh::Load(const util::TYPE_MESH& mesh) {
	const auto& [vertexcount, positions, normals, colors, uvs, uvws, indexcount, indices] = mesh;

	Load(vertexcount, positions, normals, (colors != nullptr) ? colors[0]: nullptr, (uvs != nullptr) ? uvs[0]: nullptr, (uvws != nullptr) ? uvws[0]: nullptr, indexcount, indices);
};

void lucy::Mesh::Load(const int vertexcount, const util::position_array* positions, const util::normal_array* normals, const util::color_array* color, const util::uv_array* uv, const util::uvw_array* uvw, const int indexcount, const uint32_t* indices, const glm::vec3& offset) {
	this->vertexcount = vertexcount;
	this->indexcount = indexcount;

	if (vertexcount <= 0) return;

	uint32_t flag = 0;
	if (positions != nullptr)
		flag |= lre::Vertex::position_flag;
	if (normals != nullptr)
		flag |= lre::Vertex::normal_flag;
	if (color != nullptr)
		flag |= lre::Vertex::color_flag;
	if (uv != nullptr)
		flag |= lre::Vertex::uv_flag;
	if (uvw != nullptr)
		flag |= lre::Vertex::uvw_flag;

	auto& vertex_offset = lre::Vertex::OFFSET[flag];
	int stride = vertex_offset[lre::Vertex::STRIDE];

	if (stride == 0) return;

	float* vertices = new float[vertexcount * stride * sizeof(float)];

	for (int i = 0; i < vertexcount; i++) {
		if (vertex_offset[lre::Vertex::position] >= 0) {
			if (offset != glm::vec3(0, 0, 0)) {
				*(glm::vec3*)(&vertices[i * stride + vertex_offset[lre::Vertex::position]]) = *(glm::vec3*)(&positions[i]) + offset;
			} else {
				*(glm::vec3*)(&vertices[i * stride + vertex_offset[lre::Vertex::position]]) = *(glm::vec3*)(&positions[i]);
			}
		}
		if (vertex_offset[lre::Vertex::normal] >= 0) {
			*(glm::vec3*)(&vertices[i * stride + vertex_offset[lre::Vertex::normal]]) = *(glm::vec3*)(&normals[i]);
		}
		if (vertex_offset[lre::Vertex::color] >= 0) {
			*(glm::vec4*)(&vertices[i * stride + vertex_offset[lre::Vertex::color]]) = *(glm::vec4*)(&color[i]);
		}
		if (vertex_offset[lre::Vertex::uv] >= 0) {
			*(glm::vec2*)(&vertices[i * stride + vertex_offset[lre::Vertex::uv]]) = *(glm::vec2*)(&uv[i]);
		}
		if (vertex_offset[lre::Vertex::uvw] >= 0) {
			*(glm::vec3*)(&vertices[i * stride + vertex_offset[lre::Vertex::uvw]]) = *(glm::vec3*)(&uvw[i]);
		}
	}

	vertexarray = lre::Vertex::MAP[flag]();
	if (vertexbuffer == nullptr)
		vertexbuffer = new lgl::VertexBuffer();
	if (indexbuffer == nullptr && indexcount)
		indexbuffer = new lgl::IndexBuffer();
	
	if (indexcount) {
		indexbuffer->Bind();
		indexbuffer->Allocate(sizeof(uint32_t) * indexcount);
		indexbuffer->AddData((void*)indices, sizeof(uint32_t) * indexcount);
	}

	vertexbuffer->Bind();
	vertexbuffer->Allocate(vertexcount * stride * sizeof(float));
	vertexbuffer->AddDataDynamic(vertices, vertexcount * stride * sizeof(float));

	delete[] vertices;
}
