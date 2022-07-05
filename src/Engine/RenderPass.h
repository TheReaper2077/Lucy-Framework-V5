#pragma once

#include "Renderer.h"
#include "ECS.h"

namespace lucy {
	class RenderPass {
	protected:
		Renderer& renderer = Registry::GetInstance().store<Renderer>();
		Registry& registry = Registry::GetInstance();

	public:
		virtual void FirstInit() = 0;

		virtual void Init() = 0;
		virtual void Render() = 0;
	};
}