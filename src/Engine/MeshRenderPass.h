#pragma once

#include "RenderPass.h"
#include "TextureStore.h"
#include <Components/Components.h>

namespace lucy {
	class MeshRenderPass: public RenderPass {
		std::set<Entity> lighting_entities;
		std::unordered_map<Material*, std::vector<Entity>> material_entities;
		lgl::Shader* mesh_shader = nullptr;

	public:
		MeshRenderPass() {}

		void FirstInit() override;
		void Init() override;
		void Render(lgl::FrameBuffer* framebuffer) override;
		void RenderMesh(Entity entity);
		void RenderMesh(Transform& transform, MeshRenderer& meshrenderer, Mesh* mesh);
		void Render(Camera& camera);
		void Render();
	};
}
