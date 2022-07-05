#pragma once

#include <Engine/Renderer.h>

namespace lucy {
	class Editor {
		void Init();
		void Render(Renderer& renderer);
		void UIRender();
	};
}