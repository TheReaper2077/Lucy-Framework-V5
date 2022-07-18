#include "AssetLoader.h"
#include "ECS.h"
#include <Components/Components.h>
#include <Registry/Registry.h>

static auto& registry = lucy::Registry::Instance();

void process_node(const aiScene *ai_scene, aiNode *ai_node) {
	for (int i = 0; i < ai_node->mNumMeshes; i++) {
		auto* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
		auto mesh_name = std::string(ai_mesh->mName.C_Str());

		registry.store<lucy::MeshRegistry>().AddMesh(mesh_name, lucy::Mesh{ai_scene, ai_mesh});
	}

	for (int i = 0; i < ai_node->mNumChildren; i++) {
		process_node(ai_scene, ai_node->mChildren[i]);
	}
};

void lucy::AssetLoader::Init() {
	importer = new Assimp::Importer();
}

const lucy::Mesh& lucy::AssetLoader::LoadMesh(std::string filename) {
	
}

const lucy::Mesh& lucy::AssetLoader::LoadSubMesh(std::string filename) {
	
}

const lucy::Material& lucy::AssetLoader::LoadMaterial(std::string filename) {
	
}

