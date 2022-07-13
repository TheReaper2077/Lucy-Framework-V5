#include <iostream>
#include <Components/Components.h>
#include "MeshRenderPass.h"

void lucy::MeshRenderPass::FirstInit() {
	
}

void lucy::MeshRenderPass::Init() {
	if (shader == nullptr) {
		shader = new lgl::Shader("D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\mesh.vert", "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\mesh.frag");
	}
}

void lucy::MeshRenderPass::Render(lgl::FrameBuffer* framebuffer) {
	if (framebuffer != nullptr) framebuffer->Bind();

	lighting_entities.clear();
	material_entities.clear();

	shader->Bind();

	for (auto [entity, tag, transform, meshrenderer]: registry.view<Tag, Transform, MeshRenderer>().each()) {
		if (meshrenderer.enable_lighting) {
			material_entities[meshrenderer.material].push_back(entity);
			lighting_entities.insert(entity);
		} else {
			RenderMesh(transform, meshrenderer, meshrenderer.mesh);
		}
	}

	shader->UnBind();

	if (framebuffer != nullptr) framebuffer->UnBind();
}

void lucy::MeshRenderPass::RenderMesh(Entity entity) {
	auto& transform = registry.get<Transform>(entity);
	auto& meshrenderer = registry.get<MeshRenderer>(entity);

	RenderMesh(transform, meshrenderer, meshrenderer.mesh);
}

void lucy::MeshRenderPass::RenderMesh(Transform& transform, MeshRenderer& meshrenderer, Mesh* mesh) {
	if (mesh == nullptr) return;

	renderer.SetModel(transform.GetModel());

	if (mesh->indexbuffer != nullptr) {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, mesh->indexbuffer, mesh->indexcount);
	} else {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, 0, mesh->vertexcount);
	}
}

void lucy::MeshRenderPass::Render(Camera& camera) {
	if (!camera.enable) return;

	renderer.SetProjection(camera.projection);
	renderer.SetView(camera.view);
	renderer.SetModel(glm::mat4(1.0f));
	renderer.SetViewPos(camera.position);

	Render(camera.framebuffer);
}

void lucy::MeshRenderPass::Render() {
	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
		if (!camera.enable) continue;

		Render(camera);
	}
}