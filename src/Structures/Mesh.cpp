#include "Mesh.h"
#include <Engine/ECS.h>
#include <Engine/MeshVertexArrayRegistry.h>

static auto& registry = lucy::Registry::Instance();
static auto& vertexarrayregistry = registry.store<lucy::MeshVAORegistry>();

void lucy::Mesh::Transfer() {
	uint32_t tmp_flags = 0;
	if (position.size()) tmp_flags |= MeshVAOAttribFlag_POSITION;
	if (normal.size()) tmp_flags |= MeshVAOAttribFlag_NORMAL;
	if (color.size()) tmp_flags |= MeshVAOAttribFlag_COLOR;	
	if (uv.size()) tmp_flags |= MeshVAOAttribFlag_UV;

	flags = tmp_flags;

	vertexarray = vertexarrayregistry.GetVertexArray(flags);
	
	indexcount = indices.size();
	vertexcount = position.size();

	if (vertexbuffer == nullptr && vertexcount)
		vertexbuffer = new lgl::VertexBuffer();

	if (indexbuffer == nullptr && indexcount)
		indexbuffer = new lgl::IndexBuffer();

	auto* data = (float*)malloc(vertexcount * vertexarray->stride);

	int offset = 0;
	for (int i = 0; i < vertexcount; i++) {
		if (vertexarrayregistry.IsAttribPresent(vertexarray, MeshVAOAttrib_POSITION)) {
			offset = vertexarrayregistry.GetOffset(vertexarray, MeshVAOAttrib_POSITION);
			if (i < position.size()) {
				data[i * vertexarray->elem_stride + offset + 0] = position[i].x;
				data[i * vertexarray->elem_stride + offset + 1] = position[i].y;
				data[i * vertexarray->elem_stride + offset + 2] = position[i].z;
			} else {
				data[i * vertexarray->elem_stride + offset + 0] = 0;
				data[i * vertexarray->elem_stride + offset + 1] = 0;
				data[i * vertexarray->elem_stride + offset + 2] = 0;
			}
		}
		if (vertexarrayregistry.IsAttribPresent(vertexarray, MeshVAOAttrib_NORMAL)) {
			offset = vertexarrayregistry.GetOffset(vertexarray, MeshVAOAttrib_NORMAL);
			if (i < normal.size()) {
				data[i * vertexarray->elem_stride + offset + 0] = normal[i].x;
				data[i * vertexarray->elem_stride + offset + 1] = normal[i].y;
				data[i * vertexarray->elem_stride + offset + 2] = normal[i].z;
			} else {
				data[i * vertexarray->elem_stride + offset + 0] = 0;
				data[i * vertexarray->elem_stride + offset + 1] = 0;
				data[i * vertexarray->elem_stride + offset + 2] = 0;
			}
		}
		if (vertexarrayregistry.IsAttribPresent(vertexarray, MeshVAOAttrib_COLOR)) {
			offset = vertexarrayregistry.GetOffset(vertexarray, MeshVAOAttrib_COLOR);
			if (i < color.size()) {
				data[i * vertexarray->elem_stride + offset + 0] = color[i].x;
				data[i * vertexarray->elem_stride + offset + 1] = color[i].y;
				data[i * vertexarray->elem_stride + offset + 2] = color[i].z;
				data[i * vertexarray->elem_stride + offset + 3] = color[i].w;
			} else {
				data[i * vertexarray->elem_stride + offset + 0] = 0;
				data[i * vertexarray->elem_stride + offset + 1] = 0;
				data[i * vertexarray->elem_stride + offset + 2] = 0;
				data[i * vertexarray->elem_stride + offset + 3] = 0;
			}
		}
		if (vertexarrayregistry.IsAttribPresent(vertexarray, MeshVAOAttrib_UV)) {
			offset = vertexarrayregistry.GetOffset(vertexarray, MeshVAOAttrib_COLOR);
			if (i < uv.size()) {
				data[i * vertexarray->elem_stride + offset + 0] = uv[i].x;
				data[i * vertexarray->elem_stride + offset + 1] = uv[i].y;
			} else {
				data[i * vertexarray->elem_stride + offset + 0] = 0;
				data[i * vertexarray->elem_stride + offset + 1] = 0;
			}
		}
	}

	vertexbuffer->Bind();
	vertexbuffer->Allocate(vertexcount * vertexarray->stride);
	vertexbuffer->AddDataDynamic((void*)data, vertexcount * vertexarray->stride);
	vertexbuffer->UnBind();

	if (indexbuffer != nullptr) {
		indexbuffer->Bind();
		indexbuffer->AddData(indices.data(), sizeof(uint32_t) * indexcount);
		indexbuffer->UnBind();
	}

	free(data);
	data = nullptr;
}
