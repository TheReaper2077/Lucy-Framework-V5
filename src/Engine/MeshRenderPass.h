#pragma once

#include "RenderPass.h"
#include "TextureStore.h"

namespace lucy {
	class MeshRenderPass: public RenderPass {
	public:
		MeshRenderPass() {}

		void FirstInit() override;
		void Init() override;
		void Render() override;
	};
}
