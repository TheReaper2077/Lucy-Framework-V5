#include "Transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

glm::mat4 lucy::Transform::GetTranslationMatrix() {
	if (!use_translation_matrix)
		translation_matrix = glm::translate(glm::mat4(1.0f), translation);
	return translation_matrix;
}

glm::mat4 lucy::Transform::GetScaleMatrix() {
	if (!use_scale_matrix)
		scale_matrix = glm::scale(glm::mat4(1.0f), scale);
	return scale_matrix;
}

glm::quat lucy::Transform::GetRotationQuat() {
	if (!use_rotation_quat)
		rotation_quat = glm::quat(glm::radians(rotation));
	return rotation_quat;
}

glm::mat4 lucy::Transform::GetRotationMatrix() {
	if (!use_rotation_matrix)
		rotation_matrix = glm::toMat4(GetRotationQuat());
	return rotation_matrix;
}

glm::mat4 lucy::Transform::GetModelMatrix() {
	if (!use_model_matrix)
		model_matrix = GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
	return model_matrix;
}

void lucy::Transform::Clear() {
	translation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
}
