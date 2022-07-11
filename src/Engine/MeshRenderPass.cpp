#pragma once

#include <Components/Components.h>
#include "MeshRenderPass.h"

void lucy::MeshRenderPass::FirstInit() {
	
}

void lucy::MeshRenderPass::Init() {
	
}

void lucy::MeshRenderPass::Render(lgl::FrameBuffer* framebuffer) {
	if (framebuffer != nullptr) framebuffer->Bind();

	lighting_entities.clear();
	material_entities.clear();

	for (auto [entity, tag, transform, meshrenderer]: registry.view<Tag, Transform, MeshRenderer>().each()) {
		auto* mesh = meshrenderer.mesh;

		if (meshrenderer.enable_lighting) {
			material_entities[meshrenderer.material].push_back(entity);
			lighting_entities.insert(entity);
		} else {
			renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, mesh->indexbuffer, mesh->indexcount);
		}
	}

	if (framebuffer != nullptr) framebuffer->UnBind();
}

void lucy::MeshRenderPass::RenderMesh(Entity entity) {
	auto& transform = registry.get<Transform>(entity);
	auto& meshrenderer = registry.get<MeshRenderer>(entity);
	auto* mesh = meshrenderer.mesh;

	renderer.SetModel(transform.GetModel());

	if (mesh->indexbuffer) {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, mesh->indexbuffer, mesh->indexcount);
	} else {
		renderer.Render(mesh->primitive, nullptr, mesh->vertexarray, mesh->vertexbuffer, 0, mesh->vertexcount);
	}
}
