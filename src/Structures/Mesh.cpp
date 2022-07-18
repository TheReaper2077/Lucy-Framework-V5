#include "Mesh.h"
#include <iostream>
#include <Engine/ECS.h>
#include <Registry/Registry.h>

static auto& registry = lucy::Registry::Instance();
static auto& vertexarrayregistry = registry.store<lucy::MeshVAORegistry>();

lucy::Mesh::Mesh(const aiScene* ai_scene, aiMesh* ai_mesh) {
	Import(ai_scene, ai_mesh);
}

void lucy::Mesh::Import(const aiScene* ai_scene, aiMesh* ai_mesh) {
	for (int i = 0; i < ai_mesh->mNumVertices; i++) {
		if (ai_mesh->HasPositions())
			positions.push_back(glm::vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z));

		if (ai_mesh->HasNormals())
			normals.push_back(glm::vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z));
		
		if (ai_mesh->mColors[0]) {
			colors.push_back({ai_mesh->mColors[0][i].r, ai_mesh->mColors[0][i].g, ai_mesh->mColors[0][i].b, ai_mesh->mColors[0][i].a});
		}

		if (ai_mesh->mTextureCoords[0]) {
			uv.push_back({ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y});
		}
	}

	for (int i = 0; i < ai_mesh->mNumFaces; i++) {
		aiFace face = ai_mesh->mFaces[i];

		for(unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// for (int i = 0; i < ai_mesh->mNumVertices; i++) {
	// 	std::cout << glm::to_string(positions[i]) << '\n';
	// }
}

void lucy::Mesh::Transfer() {
	if (positions.size() && !disable_position) flags |= MeshVAOAttribFlag_POSITION;
	if (normals.size() && !disable_normal) flags |= MeshVAOAttribFlag_NORMAL;
	if (colors.size() && !disable_color) flags |= MeshVAOAttribFlag_COLOR;	
	if (uv.size() && !disable_uv) flags |= MeshVAOAttribFlag_UV;

	vertexarray = vertexarrayregistry.GetVertexArray(flags);	
	indexcount = indices.size();
	vertexcount = positions.size();

	auto* data = (float*)malloc(vertexcount * vertexarray->stride);

	auto& offset_array = vertexarrayregistry.GetOffset(vertexarray);
	auto& present_array = vertexarrayregistry.GetPresent(vertexarray);

	for (int i = 0; i < vertexcount; i++) {
		if (present_array[MeshVAOAttrib_POSITION]) {
			if (i < positions.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 0] = positions[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 1] = positions[i].y;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 2] = positions[i].z;
			} else {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 0] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 1] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 2] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_NORMAL]) {
			if (i < normals.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 0] = normals[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 1] = normals[i].y;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 2] = normals[i].z;
			} else {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 0] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 1] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 2] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_COLOR]) {
			if (i < colors.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 0] = colors[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 1] = colors[i].y;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 2] = colors[i].z;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 3] = colors[i].w;
			} else {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 0] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 1] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 2] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 3] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_UV]) {
			if (i < uv.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 0] = uv[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 1] = uv[i].y;
			} else {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 0] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 1] = 0;
			}
		}
	}

	
	if (vertexbuffer == nullptr && vertexcount)
		vertexbuffer = lgl::MakeVertexBuffer();

	if (indexbuffer == nullptr && indexcount)
		indexbuffer = lgl::MakeIndexBuffer();

	if (vertexcount) {
		vertexbuffer->Bind();
		vertexbuffer->Allocate(vertexcount * vertexarray->stride);
		vertexbuffer->AddDataDynamic((void*)data, vertexcount * vertexarray->stride);
		vertexbuffer->UnBind();
	}

	if (indexcount) {
		indexbuffer->Bind();
		indexbuffer->AddData(indices.data(), sizeof(uint32_t) * indexcount);
		indexbuffer->UnBind();
	}

	free(data);
	data = nullptr;
}

void lucy::Mesh::RecalculateNormals() {
	if (primitive != lgl::TRIANGLE) return;

	normals.clear();

	normals.reserve(int(positions.size() / 3) * 3);

	for (int i = 0; i < positions.size() / 3; i++) {
		auto normal = glm::cross(positions[2 + 3 * i] - positions[0 + 3 * i], positions[1 + 3 * i] - positions[0 + 3 * i]);

		normals.emplace_back(normal);
		normals.emplace_back(normal);
		normals.emplace_back(normal);
	}
}

void lucy::Mesh::ClearData() {
	positions.clear();
	normals.clear();
	colors.clear();
	uv.clear();
	uvw.clear();

	indices.clear();
	texture_store.clear();
}
