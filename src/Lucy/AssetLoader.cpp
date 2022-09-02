#include "AssetLoader.h"
#include "MeshRegistry.h"
#include <assimp/scene.h>
#include <assimp/Bitmap.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assert.h>

static auto& registry = lucy::Registry::Instance();

void process_node(const aiScene* ai_scene, aiNode* ai_node, const std::string& filepath) {
	for (int i = 0; i < ai_node->mNumMeshes; i++) {
		auto* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
		auto mesh_name = std::string(ai_mesh->mName.C_Str());

		// auto* mesh = new lucy::Mesh{ai_mesh};

		// registry.store<lucy::MeshRegistry>().Add(mesh, mesh_name, filepath);
	}

	for (int i = 0; i < ai_node->mNumChildren; i++) {
		process_node(ai_scene, ai_node->mChildren[i], filepath);
	}
}

void lucy::Assets::Initialize() {
	self->importer = new Assimp::Importer();
}

void lucy::Assets::Load(std::string filename) {
	const auto* ai_scene = self->importer->ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	assert(ai_scene && !(ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && ai_scene->mRootNode);

	process_node(ai_scene, ai_scene->mRootNode, filename);
}
