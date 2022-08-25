#pragma once

#include <Engine/ECS.h>
#include <LucyGL/LucyGL.h>

namespace lucy::Editor {
	struct EditorStatus {
		Entity editor_camera = (Entity)0;

		Entity selected_entity = (Entity)0;
		lgl::Texture* selected_texture = nullptr;

		lgl::FrameBuffer* game_fbo = nullptr;
		lgl::FrameBuffer* editor_fbo = nullptr;
	};
}