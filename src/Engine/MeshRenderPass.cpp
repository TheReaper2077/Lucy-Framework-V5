#pragma once

#include <Components/Components.h>
#include "MeshRenderPass.h"

void lucy::MeshRenderPass::FirstInit() {
	
}

void lucy::MeshRenderPass::Init() {
	
}

void lucy::MeshRenderPass::Render() {
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
}

