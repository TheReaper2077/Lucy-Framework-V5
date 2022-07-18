#pragma once

#include <LucyGL/LucyGL.h>

namespace lucy {
	class RenderPass {
	public:
		virtual void FirstInit() = 0;

		virtual void Init() = 0;
		virtual void Render(lgl::FrameBuffer* framebuffer) = 0;
	};
}