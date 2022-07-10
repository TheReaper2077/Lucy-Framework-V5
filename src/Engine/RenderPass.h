#pragma once

#include "Renderer.h"
#include "ECS.h"

namespace lucy {
	class RenderPass {
	protected:
		Renderer& renderer = Registry::Instance().store<Renderer>();
		Registry& registry = Registry::Instance();

	public:
		virtual void FirstInit() = 0;

		virtual void Init() = 0;
		virtual void Render(lgl::FrameBuffer* framebuffer) = 0;
	};
}