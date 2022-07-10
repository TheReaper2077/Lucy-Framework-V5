#pragma once

#include <glm/glm.hpp>
#include <LucyGL/API.h>

namespace lucy {
	struct Material {		
		glm::vec3 albedo;
		glm::vec3 diffuse;
		glm::vec3 ambient;
		glm::vec3 specular;

		float roughness;
		float metallic;

		lgl::Texture* albedo_map = nullptr;
		lgl::Texture* diffuse_map = nullptr;
		lgl::Texture* ambient_map = nullptr;
		lgl::Texture* specular_map = nullptr;
		lgl::Texture* emission_map = nullptr;
		lgl::Texture* roughness_map = nullptr;
		lgl::Texture* metallic_map = nullptr;
		lgl::Texture* normal_map = nullptr;

		int illum_model;
	};
}