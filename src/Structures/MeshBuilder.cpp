#include "MeshBuilder.h"
#include <iostream>
#include <Engine/ECS.h>
#include <Registry/Registry.h>

static auto& registry = lucy::Registry::Instance();
static auto& vertexarrayregistry = registry.store<lucy::MeshVAORegistry>();

void lucy::MeshBuilder::Import(aiMesh* ai_mesh) {
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
}

void lucy::MeshBuilder::Transfer() {
	flags |= MeshVAOAttribFlag_POSITION;
	if (normals.size() && enable_normal) flags |= MeshVAOAttribFlag_NORMAL;
	if (colors.size() && enable_color) flags |= MeshVAOAttribFlag_COLOR;
	if (uv.size() && enable_uv) flags |= MeshVAOAttribFlag_UV;

	mesh->vertexarray = vertexarrayregistry.GetVertexArray(flags);	
	mesh->indexcount = indices.size();
	mesh->vertexcount = positions.size();

	auto* data = (float*)malloc(mesh->vertexcount * mesh->vertexarray->stride);

	auto& offset_array = vertexarrayregistry.GetOffset(mesh->vertexarray);
	auto& present_array = vertexarrayregistry.GetPresent(mesh->vertexarray);

	for (int i = 0; i < mesh->vertexcount; i++) {
		if (present_array[MeshVAOAttrib_POSITION]) {
			if (i < positions.size()) {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 0] = positions[i].x;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 1] = positions[i].y;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 2] = positions[i].z;
			} else {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 0] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 1] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 2] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_NORMAL]) {
			if (i < normals.size()) {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 0] = normals[i].x;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 1] = normals[i].y;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 2] = normals[i].z;
			} else {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 0] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 1] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 2] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_COLOR]) {
			if (i < colors.size()) {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 0] = colors[i].x;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 1] = colors[i].y;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 2] = colors[i].z;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 3] = colors[i].w;
			} else {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 0] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 1] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 2] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 3] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_UV]) {
			if (i < uv.size()) {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 0] = uv[i].x;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 1] = uv[i].y;
			} else {
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 0] = 0;
				data[i * mesh->vertexarray->elem_stride + offset_array[MeshVAOAttrib_UV] + 1] = 0;
			}
		}
	}

	
	if (mesh->vertexbuffer == nullptr && mesh->vertexcount)
		mesh->vertexbuffer = lgl::MakeVertexBuffer();

	if (mesh->indexbuffer == nullptr && mesh->indexcount)
		mesh->indexbuffer = lgl::MakeIndexBuffer();

	if (mesh->vertexcount) {
		mesh->vertexbuffer->Bind();
		mesh->vertexbuffer->Allocate(mesh->vertexcount * mesh->vertexarray->stride);
		mesh->vertexbuffer->AddDataDynamic((void*)data, mesh->vertexcount * mesh->vertexarray->stride);
		mesh->vertexbuffer->UnBind();
	}

	if (mesh->indexcount) {
		mesh->indexbuffer->Bind();
		mesh->indexbuffer->AddData(indices.data(), sizeof(uint32_t) * mesh->indexcount);
		mesh->indexbuffer->UnBind();
	}

	free(data);
	data = nullptr;
}

void lucy::MeshBuilder::RecalculateNormals() {
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

void lucy::MeshBuilder::ClearData() {
	positions.clear();
	normals.clear();
	colors.clear();
	uv.clear();
	uvw.clear();

	indices.clear();
}