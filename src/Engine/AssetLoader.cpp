#include "AssetLoader.h"
#include "ECS.h"
#include <Components/Components.h>
#include <Registry/Registry.h>

static auto& registry = lucy::Registry::Instance();
static auto& materialregistry = registry.store<lucy::MaterialRegistry>();
static auto& meshregistry = registry.store<lucy::MeshRegistry>();

void process_node(const aiScene *ai_scene, aiNode *ai_node) {
	for (int i = 0; i < ai_node->mNumMeshes; i++) {
		auto* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
		auto mesh_name = std::string(ai_mesh->mName.C_Str());

		lucy::MeshBuilder meshbuilder;
		meshbuilder.Import(ai_mesh);

		// registry.store<lucy::MeshRegistry>().AddMesh(mesh_name, meshbuilder);
	}

	for (int i = 0; i < ai_node->mNumChildren; i++) {
		process_node(ai_scene, ai_node->mChildren[i]);
	}
};

void lucy::AssetLoader::Init() {
	auto& instance = Instance();

	instance.importer = new Assimp::Importer();
}

const aiScene* lucy::AssetLoader::Import(std::string filepath, uint32_t flags) {
	auto& instance = Instance();

	const auto* ai_scene = instance.importer->ReadFile(filepath.c_str(), flags | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (ai_scene == nullptr)
		return nullptr;

	assert(ai_scene && !(ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && ai_scene->mRootNode);

	if (ai_scene->HasMaterials()) {
		for (int i = 0; i < ai_scene->mNumMaterials; i++)
			materialregistry.AddMaterial(ai_scene->mMaterials[i]);
	}

	if (ai_scene->HasMeshes()) {
		for (int i = 0; i < ai_scene->mNumMeshes; i++) {
			// auto id = meshregistry.AddMesh(ai_scene->mMeshes[i]->mName.C_Str(), ai_scene->mMeshes[i]);
			// meshregistry.GetMesh(id)->Transfer();
		}
	}

	return ai_scene;
}