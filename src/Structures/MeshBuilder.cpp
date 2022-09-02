#include "MeshBuilder.h"

// void lucy::MeshBuilder::Load(aiMesh* ai_mesh) {
// 	for (int i = 0; i < ai_mesh->mNumVertices; i++) {
// 		if (ai_mesh->HasPositions()) {
// 			positions.push_back(glm::vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z));
// 		}

// 		if (ai_mesh->HasNormals())
// 			normals.push_back(glm::vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z));
		
// 		if (ai_mesh->mColors[0]) {
// 			color.push_back({ai_mesh->mColors[0][i].r, ai_mesh->mColors[0][i].g, ai_mesh->mColors[0][i].b, ai_mesh->mColors[0][i].a});
// 		}

// 		if (ai_mesh->mTextureCoords[0]) {
// 			uv.push_back({ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y});
// 		}
// 	}

// 	for (int i = 0; i < ai_mesh->mNumFaces; i++) {
// 		aiFace face = ai_mesh->mFaces[i];

// 		for(unsigned int j = 0; j < face.mNumIndices; j++) {
// 			indices.push_back(face.mIndices[j]);
// 		}
// 	}
// }

void lucy::MeshBuilder::Load(std::string filename, std::string mesh_name) {
	// auto* ai_mesh = 
}

void lucy::MeshBuilder::Build() {
	if (mesh == nullptr)
		mesh = new Mesh;

	
}

