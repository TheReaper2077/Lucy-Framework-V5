#pragma once

#include "RenderPass.h"

namespace lucy {
	class SpriteRenderPass: public RenderPass {
	public:
		void FirstInit() override;
		void Init() override;
		void Render() override;
	};
}