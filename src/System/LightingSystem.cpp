#include "LightingSystem.h"
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <Registry/Registry.h>

void lucy::LightingSystem(Registry& registry) {
	auto& renderer = registry.store<Renderer>();

	renderer.directional_light_count = 0;
	renderer.point_light_count = 0;
	
	for (auto [entity, tag, transform, light]: registry.view<Tag, Transform, Light>().each()) {
		renderer.directional_light_count += (light.mode == DIRECTIONAL_LIGHT);
		renderer.point_light_count += (light.mode == POINT_LIGHT);
	}

	auto directional_light_count = renderer.directional_light_count;
	auto point_light_count = renderer.point_light_count;

	auto* shader = renderer.GetPBRShader("pbrmesh");

	shader->Bind();

	for (auto [entity, tag, transform, light]: registry.view<Tag, Transform, Light>().each()) {
		if (light.mode == DIRECTIONAL_LIGHT) {
			auto direction = glm::normalize(transform.GetRotationQuat() * glm::vec3(0, -1.0, 0));
			auto dir_light = "dir_light" + std::to_string(directional_light_count);

			directional_light_count--;

			shader->SetUniformVec3(dir_light + ".position", &transform.translation[0]);
			shader->SetUniformVec3(dir_light + ".color", &light.color[0]);
			shader->SetUniformVec3(dir_light + ".direction", &direction[0]);
		}
		if (light.mode == POINT_LIGHT) {
			point_light_count--;

			auto point_light = "point_light" + std::to_string(point_light_count);

			shader->SetUniformVec3(point_light + ".position", &transform.translation[0]);
			shader->SetUniformVec3(point_light + ".color", &light.color[0]);
		}
	}

	shader->UnBind();
}

