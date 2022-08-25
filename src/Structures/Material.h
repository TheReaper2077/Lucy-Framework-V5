#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lucy {
	struct Material {
		glm::vec3 albedo = { 1, 0, 0 };
		glm::vec3 diffuse = { 0.2, 0.001, 0.8 };
		glm::vec3 ambient = { 0.5, 0.6, 0.5 };
		glm::vec3 specular = { 1, 0, 0 };

		float roughness = 0.6;
		float metallic = 0.0;
		float shininess = 0.0;

		lgl::Texture* albedo_map = nullptr;
		lgl::Texture* diffuse_map = nullptr;
		lgl::Texture* ambient_map = nullptr;
		lgl::Texture* specular_map = nullptr;
		lgl::Texture* emission_map = nullptr;
		lgl::Texture* roughness_map = nullptr;
		lgl::Texture* metallic_map = nullptr;
		lgl::Texture* normal_map = nullptr;

		int illum_model;

		std::string name = "New Material";
		std::string id = "ID_NONE";

		lgl::Shader* shader = nullptr;

		bool use_shader = false;

		uint32_t flags = 0;

		Material() {}
		~Material() {}

		Material(aiMaterial *ai_material);
		void Import(aiMaterial *ai_material);
	};
}
