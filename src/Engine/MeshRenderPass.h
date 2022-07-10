#pragma once

#include "RenderPass.h"
#include "TextureStore.h"
#include <Components/Components.h>

namespace lucy {
	class MeshRenderPass: public RenderPass {
		std::set<Entity> lighting_entities;
		std::unordered_map<Material*, std::vector<Entity>> material_entities;

	public:
		MeshRenderPass() {}

		void FirstInit() override;
		void Init() override;
		void Render(lgl::FrameBuffer* framebuffer) override;
	};
}
