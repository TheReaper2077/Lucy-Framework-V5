#include <iostream>
#include <Components/Components.h>
#include "MeshRenderPass.h"

void lucy::MeshRenderPass::FirstInit() {
	renderer.SetShader("mesh", "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\mesh.vert", "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\mesh.frag");
	renderer.SetShader("pbrmesh", "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\mesh.vert", "D:\\C++\\Lucy Framework V5\\src\\Engine\\Shaders\\Default\\pbr.frag");
}

void lucy::MeshRenderPass::Init() {
	
}

void lucy::MeshRenderPass::Render(lgl::FrameBuffer* framebuffer) {
	if (framebuffer != nullptr) framebuffer->Bind();

	lighting_entities.clear();
	material_entities.clear();

	for (auto [entity, tag, transform, meshrenderer]: registry.view<Tag, Transform, MeshRenderer>().each()) {
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

// void lucy::MeshRenderPass::Render(Camera& camera) {
// 	if (!camera.enable) return;

// 	renderer.SetProjection(camera.projection);
// 	renderer.SetView(camera.view);
// 	renderer.SetModel(glm::mat4(1.0f));
// 	renderer.SetViewPos(camera.position);

// 	Render(camera.framebuffer);
// }

// void lucy::MeshRenderPass::Render() {
// 	for (auto [entity, tag, transform, camera]: registry.view<Tag, Transform, Camera>().each()) {
// 		if (!camera.enable) continue;

// 		Render(camera);
// 	}
// }

// shader->SetUniformVec3("material.albedo", &material.albedo[0]);
// shader->SetUniformf("material.metallic", material.metallic);
// shader->SetUniformf("material.roughness", material.roughness);
// shader->SetUniformf("material.ao", 1.0f);

	// // shader->SetUniformVec3("material.ambient", &material.ambient[0]);
	// // shader->SetUniformVec3("material.diffuse", &material.diffuse[0]);
	// // shader->SetUniformVec3("material.specular", &material.specular[0]);

	// // shader->SetUniformVec3("material.albedo", &material.albedo[0]);
	// // shader->SetUniformf("material.metallic", material.metallic);
	// // shader->SetUniformf("material.roughness", material.roughness);
	
	// shader->SetUniformVec3("material.albedo", &material.albedo[0]);
	// shader->SetUniformf("material.metallic", material.metallic);
	// shader->SetUniformf("material.roughness", material.roughness);
	// shader->SetUniformf("material.ao", 1.0f);

	// // shader->SetUniformf("material.shininess", material.shininess);

	// if (material.ambient_map != nullptr) {
	// 	glActiveTexture(GL_TEXTURE0);
	// 	material.ambient_map->BindUnit(0);
	// 	shader->SetUniformi("material.ambient_map", 0);
	// 	shader->SetUniformi("ambient_index", 1);
	// } else {
	// 	shader->SetUniformi("ambient_index", 0);
	// }

	// if (material.diffuse_map != nullptr) {
	// 	glActiveTexture(GL_TEXTURE1);
	// 	material.diffuse_map->BindUnit(1);
	// 	shader->SetUniformi("material.diffuse_map", 1);
	// 	shader->SetUniformi("diffuse_index", 1);
	// } else {
	// 	shader->SetUniformi("diffuse_index", 0);
	// }

	// if (material.specular_map != nullptr) {
	// 	glActiveTexture(GL_TEXTURE2);
	// 	material.specular_map->BindUnit(2);
	// 	shader->SetUniformi("material.specular_map", 2);
	// 	shader->SetUniformi("specular_index", 1);
	// } else {
	// 	shader->SetUniformi("specular_index", 0);
	// }