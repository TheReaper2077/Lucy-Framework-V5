#include "Mesh.h"
#include <Engine/ECS.h>
#include <Engine/MeshVertexArrayRegistry.h>

static auto& registry = lucy::Registry::Instance();
static auto& vertexarrayregistry = registry.store<lucy::MeshVAORegistry>();

void lucy::Mesh::Transfer() {
	if (position.size() && !disable_position) flags |= MeshVAOAttribFlag_POSITION;
	if (normal.size() && !disable_normal) flags |= MeshVAOAttribFlag_NORMAL;
	if (color.size() && !disable_color) flags |= MeshVAOAttribFlag_COLOR;	
	if (uv.size() && !disable_uv) flags |= MeshVAOAttribFlag_UV;

	vertexarray = vertexarrayregistry.GetVertexArray(flags);	
	indexcount = indices.size();
	vertexcount = position.size();

	auto* data = (float*)malloc(vertexcount * vertexarray->stride);

	auto& offset_array = vertexarrayregistry.GetOffset(vertexarray);
	auto& present_array = vertexarrayregistry.GetPresent(vertexarray);

	for (int i = 0; i < vertexcount; i++) {
		if (present_array[MeshVAOAttrib_POSITION]) {
			if (i < position.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 0] = position[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 1] = position[i].y;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 2] = position[i].z;
			} else {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 0] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 1] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_POSITION] + 2] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_NORMAL]) {
			if (i < normal.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 0] = normal[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 1] = normal[i].y;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 2] = normal[i].z;
			} else {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 0] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 1] = 0;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_NORMAL] + 2] = 0;
			}
		}
		if (present_array[MeshVAOAttrib_COLOR]) {
			if (i < color.size()) {
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 0] = color[i].x;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 1] = color[i].y;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 2] = color[i].z;
				data[i * vertexarray->elem_stride + offset_array[MeshVAOAttrib_COLOR] + 3] = color[i].w;
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
		vertexbuffer = new lgl::VertexBuffer();

	if (indexbuffer == nullptr && indexcount)
		indexbuffer = new lgl::IndexBuffer();

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
