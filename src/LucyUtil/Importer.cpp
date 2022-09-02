#include "Importer.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assert.h>

lutil::TYPE_MESH LoadMesh(aiMesh* ai_mesh);

#define ai_importer ImporterInstance()
static Assimp::Importer* ImporterInstance() {
	static Assimp::Importer* instance = nullptr;
	if (instance == nullptr)
		instance = new Assimp::Importer();
	return instance;
}

lutil::TYPE_MESH lutil::LoadMesh(const std::string& filename, const std::string& mesh_name) {
	const auto* ai_scene = ai_importer->ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!(ai_scene && !(ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && ai_scene->mRootNode)) {
		return { -2, nullptr, nullptr, nullptr, nullptr, nullptr, 0, nullptr };
	}

	aiMesh* ai_mesh = nullptr;
	for (int i = 0; i < ai_scene->mNumMeshes; i++) {
		ai_mesh = ai_scene->mMeshes[i];
		if (mesh_name == std::string(ai_mesh->mName.C_Str()))
			break;
		ai_mesh = nullptr;
	}

	if (ai_mesh == nullptr) {
		return { -1, nullptr, nullptr, nullptr, nullptr, nullptr, 0, nullptr };
	}


	auto tmp = LoadMesh(ai_mesh);

	ai_importer->FreeScene();

	return tmp;
}

inline lutil::TYPE_MESH LoadMesh(aiMesh* ai_mesh) {
	int indexcount = 0;
	int vertexcount = ai_mesh->mNumVertices;

	lutil::position_array* position_array = nullptr;
	lutil::normal_array* normal_array = nullptr;
	lutil::color_2d_array* color_array = nullptr;
	lutil::uv_2d_array* uv_array = nullptr;
	lutil::uvw_2d_array* uvw_array = nullptr;
	uint32_t* indices = nullptr;

	if (vertexcount > 0) {
		if (ai_mesh->HasPositions())
			position_array = new lutil::position_array[vertexcount];
		if (ai_mesh->HasNormals())
			normal_array = new lutil::normal_array[vertexcount];

		for (int i = 0; i < ai_mesh->GetNumColorChannels(); i++) {
			if (color_array == nullptr)
				color_array = new lutil::color_2d_array[AI_MAX_NUMBER_OF_COLOR_SETS];

			color_array[i] = new lutil::color_array[vertexcount];
		}

		for (int i = 0; i < 8; i++) {
			if (ai_mesh->mNumUVComponents[i] == 2) {
				if (uv_array == nullptr) {
					uv_array = new lutil::uv_2d_array[8];

					for (int idx = 0; idx < 8; idx++)
						uv_array[idx] = nullptr;
				}

				uv_array[i] = new lutil::uv_array[vertexcount];
			}
			if (ai_mesh->mNumUVComponents[i] == 3) {
				if (uvw_array == nullptr) {
					uvw_array = new lutil::uvw_2d_array[8];

					for (int idx = 0; idx < 8; idx++)
						uvw_array[idx] = nullptr;
				}

				uvw_array[i] = new lutil::uvw_array[vertexcount];
			}
		}

		for (int i = 0; i < vertexcount; i++) {
			if (position_array != nullptr) {
				position_array[i] = *(glm::vec3*)&ai_mesh->mVertices[i];
			}
			if (normal_array != nullptr) {
				normal_array[i] = *(glm::vec3*)&ai_mesh->mVertices[i];
			}
			if (color_array != nullptr) {
				for (int idx = 0; idx < 8; idx++) {
					if (color_array[idx] == nullptr)
						break;
					color_array[idx][i] = *(glm::vec4*)&ai_mesh->mColors[idx][i];
				}
			}
			if (uv_array != nullptr) {
				for (int idx = 0; idx < 8; idx++)
					if (uv_array[idx] != nullptr)
						uv_array[idx][i] = *(glm::vec2*)&ai_mesh->mTextureCoords[idx][i];
			}
			if (uvw_array != nullptr) {
				for (int idx = 0; idx < 8; idx++)
					if (uvw_array[idx] != nullptr)
						uvw_array[idx][i] = *(glm::vec3*)&ai_mesh->mTextureCoords[idx][i];
			}
		}

		if (ai_mesh->HasFaces()) {
			for (int i = 0; i < ai_mesh->mNumFaces; i++)
				indexcount += ai_mesh->mFaces[i].mNumIndices;

			indices = new uint32_t[indexcount];

			int idx = 0;
			for (int i = 0; i < ai_mesh->mNumFaces; i++) {
				aiFace face = ai_mesh->mFaces[i];

				for(int j = 0; j < face.mNumIndices; j++)
					indices[idx++] = face.mIndices[j];
			}
		}
	}

	return { vertexcount, position_array, normal_array, color_array, uv_array, uvw_array, indexcount, indices };
}
