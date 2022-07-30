#include <iostream>
#include <Components/Components.h>
#include <glm/gtx/string_cast.hpp>

static auto& registry = lucy::Registry::Instance();
static auto& renderer = lucy::Registry::Instance().store<lucy::Renderer>();

void lucy::Renderer::Render(lgl::FrameBuffer* framebuffer) {
	lighting_entities.clear();
	material_entities.clear();

	for (auto [entity, tag, transform, meshrenderer]: registry.view<Tag, Transform, MeshRenderer>().each()) {
		if (meshrenderer.mesh == nullptr) continue;
		
		if (meshrenderer.enable_lighting) {
			lighting_entities.insert(entity);
		}

		material_entities[meshrenderer.material].push_back(entity);
	}

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
			RenderMesh(entity);
		}
	}

	auto* normal_shader = renderer.GetShader("mesh");

	normal_shader->Bind();

	for (auto entity: material_entities[nullptr]) {
		RenderMesh(entity);
	}

	normal_shader->UnBind();
}

void lucy::Renderer::RenderMesh(Entity entity) {
	auto& transform = registry.get<Transform>(entity);
	auto& meshrenderer = registry.get<MeshRenderer>(entity);

	RenderMesh(transform, meshrenderer, meshrenderer.mesh);
}

void lucy::Renderer::RenderMesh(Transform& transform, MeshRenderer& meshrenderer, Mesh* mesh) {
	if (mesh == nullptr) return;

	renderer.SetModel(transform.GetModel());

	if (mesh->indexbuffer != nullptr) {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, mesh->indexbuffer, mesh->indexcount);
	} else {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, 0, mesh->vertexcount);
	}
}
