#pragma once

#include "ECS.h"

namespace lucy {
	struct Functions {
		Entity main_camera = (Entity)0;
		bool enable_debug_render = false;
		bool render_target_to_screen = true;
		bool enable_physics_caching = true;

		bool physics_pause = false;
		bool physics_play = false;
		bool physics_stop = false;

		void SetCameraEntity(const Entity& entity);
		Entity GetCameraEntity();
		void EnableDebugRender(bool enable);

		void PlayPhysics();
		void StopPhysics();
		void PausePhysics();
		bool IsPhysicsPlaying();
		bool IsPhysicsStopped();
		bool IsPhysicsPaused();
	};
}