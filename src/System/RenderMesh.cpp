#include "RenderMesh.h"

#include <Engine/ECS.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <Registry/Registry.h>
#include <set>
#include <unordered_map>

void RenderMesh(lucy::Renderer& renderer, lucy::Transform& transform, lucy::MeshRenderer& meshrenderer, lucy::Mesh* mesh) {
	if (mesh == nullptr) return;

	renderer.SetModel(transform.GetModel());

	if (mesh->indexbuffer != nullptr) {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, mesh->indexbuffer, mesh->indexcount);
	} else {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, 0, mesh->vertexcount);
	}
}

void RenderMesh(lucy::Registry& registry, lucy::Renderer& renderer, lucy::Entity entity) {
	auto& transform = registry.get<lucy::Transform>(entity);
	auto& meshrenderer = registry.get<lucy::MeshRenderer>(entity);

	RenderMesh(renderer, transform, meshrenderer, meshrenderer.mesh);
}

static std::set<lucy::Entity> lighting_entities;
static std::unordered_map<lucy::Material*, std::vector<lucy::Entity>> material_entities;

void lucy::MeshRenderSystem(Registry& registry, Renderer& renderer) {
	lighting_entities.clear();
	material_entities.clear();

	for (auto [entity, tag, transform, meshrenderer]: registry.view<Tag, Transform, MeshRenderer>().each()) {
		if (meshrenderer.mesh == nullptr) continue;
		
		if (meshrenderer.enable_lighting) {
			lighting_entities.insert(entity);
		}

		material_entities[meshrenderer.material].push_back(entity);
	}

	if (!material_entities.size()) return;

	auto* pbr_shader = renderer.GetPBRShader("pbrmesh");

	pbr_shader->Bind();

	for (auto& pair: material_entities) {
		auto* material = pair.first;

		if (material == nullptr)
			continue;

		// std::cout << glm::to_string(material->albedo) << ' ' << material->name << '\n';

		pbr_shader->SetUniformVec3("material.albedo", &material->albedo[0]);
		pbr_shader->SetUniformf("material.metallic", material->metallic);
		pbr_shader->SetUniformf("material.roughness", material->roughness);
		pbr_shader->SetUniformf("material.ao", 1.0f);

		for (auto entity: pair.second) {
			RenderMesh(registry, renderer, entity);
		}
	}

	auto* normal_shader = renderer.GetShader("mesh");

	normal_shader->Bind();

	for (auto entity: material_entities[nullptr]) {
		RenderMesh(registry, renderer, entity);
	}

	normal_shader->UnBind();
}
