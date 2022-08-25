#pragma once

namespace lucy {
	struct ComponentTemplate {
		virtual void ImGuiRender() = 0;
	};
}