#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"

namespace lucy {
	struct Transform {
		glm::vec3 translation = { 0, 0, 0 };
		glm::vec3 rotation = { 0, 0, 0 };
		glm::vec3 scale = { 1, 1, 1 };

		bool use_rotation_quat = false;
		glm::quat rotation_quat;

		bool use_translation_matrix = false;
		glm::mat4 translation_matrix;
		
		bool use_rotation_matrix = false;
		glm::mat4 rotation_matrix;

		bool use_scale_matrix = false;
		glm::mat4 scale_matrix;

		bool use_model_matrix = false;
		glm::mat4 model_matrix;

		Transform* parent_entity = nullptr;

		Transform() {}
		Transform(const glm::vec3& translation): translation(translation) {}

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::quat GetRotationQuat();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetModelMatrix();

		void Clear();
	};
}