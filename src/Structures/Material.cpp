#include "Material.h"

lucy::Material::Material(aiMaterial *ai_material) {
	name = std::string(ai_material->GetName().C_Str());

	aiString str;
	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
		ai_material->GetTexture(aiTextureType_DIFFUSE, i, &str);

		diffuse_map = lgl::MakeTexture();
		diffuse_map->Bind();
		diffuse_map->LoadTexture(str.C_Str());
		diffuse_map->UnBind();
		break;
	}

	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_AMBIENT); i++) {
		ai_material->GetTexture(aiTextureType_AMBIENT, i, &str);

		ambient_map = lgl::MakeTexture();
		ambient_map->Bind();
		ambient_map->LoadTexture(str.C_Str());
		ambient_map->UnBind();
		break;
	}

	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_SPECULAR); i++) {
		ai_material->GetTexture(aiTextureType_SPECULAR, i, &str);

		specular_map = lgl::MakeTexture();
		specular_map->Bind();
		specular_map->LoadTexture(str.C_Str());
		specular_map->UnBind();
		break;
	}

	for (int i = 0; i < ai_material->GetTextureCount(aiTextureType_EMISSIVE); i++) {
		ai_material->GetTexture(aiTextureType_EMISSIVE, i, &str);

		emission_map = lgl::MakeTexture();
		emission_map->Bind();
		emission_map->LoadTexture(str.C_Str());
		emission_map->UnBind();
		break;
	}

	aiColor4D color;
	
	if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_AMBIENT, &color)) {
		ambient = { color.r, color.g, color.b };
	}
	
	if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
		diffuse = { color.r, color.g, color.b };
	}

	if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_SPECULAR, &color)) {
		specular = { color.r, color.g, color.b };
	}

	if (AI_SUCCESS != aiGetMaterialFloat(ai_material, AI_MATKEY_SHININESS, &shininess)) {
		shininess = 20.f;
	}
}
