#pragma once

#include <Engine/ECS.h>
#include <LucyGL/LucyGL.h>


namespace lucy::Editor {
	struct EditorStatus {
		Entity editor_camera = (Entity)0;

		lgl::FrameBuffer* game_fbo = nullptr;
		lgl::FrameBuffer* editor_fbo = nullptr;
	};
}