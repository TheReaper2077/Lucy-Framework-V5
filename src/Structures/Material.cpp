#include "Material.h"

lucy::Material::Material(aiMaterial *ai_material) {
	aiString str;
	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
		ai_material->GetTexture(aiTextureType_DIFFUSE, i, &str);

		this->diffuse_map = lgl::MakeTexture(str.C_Str());
		flags |= MAT_DIFFUSE_TEXTURE_BIT;
		break;
	}

	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_AMBIENT); i++) {
		ai_material->GetTexture(aiTextureType_AMBIENT, i, &str);

		this->ambient_map = lgl::MakeTexture(str.C_Str());
		flags |= MAT_AMBIENT_TEXTURE_BIT;
		break;
	}

	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_SPECULAR); i++) {
		ai_material->GetTexture(aiTextureType_SPECULAR, i, &str);

		this->specular_map = lgl::MakeTexture(str.C_Str());
		flags |= MAT_SPECULAR_TEXTURE_BIT;
		break;
	}

	name = std::string(ai_material->GetName().C_Str());

	aiColor4D color;
	
	if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_AMBIENT, &color)) {
		this->ambient = glm::vec3(color.r, color.g, color.b);
		// flags |= MAT_AMBIENT_COLOR_BIT;
	}
	
	if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
		this->diffuse = glm::vec3(color.r, color.g, color.b);
		// flags |= MAT_DIFFUSE_COLOR_BIT;
	}

	if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_SPECULAR, &color)) {
		this->specular = glm::vec3(color.r, color.g, color.b);
		// flags |= MAT_SPECULAR_COLOR_BIT;
	}

	if (AI_SUCCESS != aiGetMaterialFloat(ai_material, AI_MATKEY_SHININESS, &shininess)) {
		this->shininess = 20.f;
		// flags |= MAT_SHININESS_FLOAT_BIT;
	}
}
