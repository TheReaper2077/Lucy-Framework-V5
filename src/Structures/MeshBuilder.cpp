#include "MeshBuilder.h"
#include <LucyUtil/LucyUtil.h>

void lucy::MeshBuilder::Load(std::string filename, std::string mesh_name) {
	auto mesh = util::LoadMesh(filename, mesh_name);

	Load(mesh);

	util::Free(mesh);
}

void lucy::MeshBuilder::Load(const util::TYPE_MESH& mesh) {
	auto& [vertexcount, positions, normals, colors, uvs, uvws, indexcount, indices] = mesh;

	if (vertexcount > 0) {
		if (positions != nullptr) {
			this->positions = std::vector<util::position_array>(positions, positions + vertexcount);
		}
		if (normals != nullptr) {
			this->normals = std::vector<util::normal_array>(normals, normals + vertexcount);
		}
		if (colors != nullptr) {
			for (int i = 0; i < 8; i++)
				if (colors[i] != nullptr)
					this->color[i] = std::vector<util::color_array>(colors[i], colors[i] + vertexcount);
		}
		if (uvs != nullptr) {
			for (int i = 0; i < 8; i++)
				if (uvs[i] != nullptr)
					this->uv[i] = std::vector<util::uv_array>(uvs[i], uvs[i] + vertexcount);
		}
		if (uvws != nullptr) {
			for (int i = 0; i < 8; i++)
				if (uvws[i] != nullptr)
					this->uvw[i] = std::vector<util::uvw_array>(uvws[i], uvws[i] + vertexcount);
		}
	}

	if (indexcount > 0) {
		if (indices != nullptr)
			this->indices  = std::vector<uint32_t>(indices, indices + indexcount);
	}
}

void lucy::MeshBuilder::Build() {
	if (mesh != nullptr) {
		mesh = new Mesh;
	}

	mesh->Load(positions.size(), positions.data(), normals.data(), color[0].data(), uv[0].data(), uvw[0].data(), indices.size(), indices.data());
}
