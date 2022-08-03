#include "MainRenderer.h"
#include <Components/Components.h>

void RenderMesh(lucy::Transform& transform, lucy::MeshRenderer& meshrenderer, lucy::Mesh* mesh) {
	if (mesh == nullptr) return;

	lre::SetModel(transform.GetModel());

	if (mesh->indexbuffer != nullptr) {
		lre::Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, mesh->indexbuffer, mesh->indexcount);
	} else {
		lre::Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, 0, mesh->vertexcount);
	}
}

void RenderMesh(lucy::Registry& registry, lucy::Entity entity) {
	auto& transform = registry.get<lucy::Transform>(entity);
	auto& meshrenderer = registry.get<lucy::MeshRenderer>(entity);

	RenderMesh(transform, meshrenderer, meshrenderer.mesh);
}

void lucy::MainRenderer::MeshRender(Registry& registry) {
	if (!mesh_material_entities.size()) return;

	// pbr_mesh_shader->Bind();

	// for (auto& pair: mesh_material_entities) {
	// 	auto* material = pair.first;

	// 	if (material == nullptr)
	// 		continue;

	// 	pbr_mesh_shader->SetUniformVec3("material.albedo", &material->albedo[0]);
	// 	pbr_mesh_shader->SetUniformf("material.metallic", material->metallic);
	// 	pbr_mesh_shader->SetUniformf("material.roughness", material->roughness);
	// 	pbr_mesh_shader->SetUniformf("material.ao", 1.0f);

	// 	for (auto entity: pair.second) {
	// 		RenderMesh(registry, entity);
	// 	}
	// }

	// mesh_shader->Bind();

	// for (auto entity: mesh_material_entities[nullptr]) {
	// 	if (registry.contains<MeshRenderer>(entity))
	// 		RenderMesh(registry, entity);
	// }

	// mesh_shader->UnBind();
}