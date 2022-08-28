#include "Mesh.h"
#include <LucyRE/LucyRE.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

lucy::Mesh::Mesh(aiMesh* ai_mesh) {
	vertexcount = ai_mesh->mNumVertices;

	uint64_t flag = 0;
	if (ai_mesh->HasPositions())
		flag |= lre::Vertex::position_flag;
	if (ai_mesh->HasNormals())
		flag |= lre::Vertex::normal_flag;
	if (ai_mesh->mColors[0])
		flag |= lre::Vertex::color_flag;
	// if (ai_mesh->mTextureCoords[0])
	// 	flag |= lre::Vertex::uv_flag;

	auto& offset = lre::Vertex::OFFSET[flag];
	int stride = offset[lre::Vertex::INDEX_COUNT];

	if (stride == 0) return;

	float* vertices = (float*)malloc(vertexcount * stride * sizeof(float));

	for (int i = 0; i < vertexcount; i++) {
		if (offset[lre::Vertex::position] >= 0) {
			*(glm::vec3*)(&vertices[i * stride + offset[lre::Vertex::position]]) = *(glm::vec3*)(&ai_mesh->mVertices[i]);
			// std::cout << glm::to_string(*(glm::vec3*)(&vertices[i * stride + offset[lre::Vertex::position]])) << '\n';
		}

		if (offset[lre::Vertex::normal] >= 0) {
			*(glm::vec3*)(&vertices[i * stride + offset[lre::Vertex::normal]]) = *(glm::vec3*)(&ai_mesh->mNormals[i]);
			// std::cout << glm::to_string(*(glm::vec3*)(&vertices[i * stride + offset[lre::Vertex::normal]])) << '\n';
		}
		
		if (offset[lre::Vertex::color] >= 0) {
			*(glm::vec4*)(&vertices[i * stride + offset[lre::Vertex::color]]) = *(glm::vec4*)(&ai_mesh->mColors[0][i]);
			// std::cout << glm::to_string(*(glm::vec4*)(&vertices[i * stride + offset[lre::Vertex::color]])) << '\n';
		}

		if (offset[lre::Vertex::uv] >= 0) {
			*(glm::vec2*)(&vertices[i * stride + offset[lre::Vertex::uv]]) = *(glm::vec2*)(&ai_mesh->mTextureCoords[0][i]);
			// std::cout << glm::to_string(*(glm::vec2*)(&vertices[i * stride + offset[lre::Vertex::uv]])) << '\n';
		}
	}

	std::vector<uint32_t> indices;

	for (int i = 0; i < ai_mesh->mNumFaces; i++) {
		aiFace face = ai_mesh->mFaces[i];

		for(unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	indexcount = indices.size();
	vertexarray = lre::Vertex::MAP[flag]();

	if (vertexbuffer == nullptr)
		vertexbuffer = new lgl::VertexBuffer();
	if (indexbuffer == nullptr && indexcount)
		indexbuffer = new lgl::IndexBuffer();

	if (indexcount) {
		indexbuffer->Bind();
		indexbuffer->Allocate(sizeof(uint32_t) * indexcount);
		indexbuffer->AddData(indices.data(), sizeof(uint32_t) * indexcount);
	}

	vertexbuffer->Bind();
	vertexbuffer->Allocate(vertexcount * stride * sizeof(float));
	vertexbuffer->AddDataDynamic(vertices, vertexcount * stride * sizeof(float));

	free(vertices);
}
