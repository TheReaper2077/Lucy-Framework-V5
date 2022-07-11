#pragma once

#include "System.h"
#include <Engine/ECS.h>

namespace lucy {
	class CameraSystem: public System {
	public:
		void Update();

	private:
		void FPSView(Entity entity);
		void EditorView(Entity entity);
	};
}