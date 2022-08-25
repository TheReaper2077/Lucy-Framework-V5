#pragma once

#include "ECS.h"
#include <glm/glm.hpp>

namespace lucy {
	struct Functions {
		Entity main_camera = (Entity)0;
		bool enable_physics_object_render = false;
		bool render_target_to_screen = true;
		bool enable_physics_caching = true;

		int32_t velocity_iterations = 6;
		int32_t position_iterations = 2;

		glm::vec2 render_resolution = { 1280, 640 };

		enum PhysicsState {
			STOP,
			PAUSE,
			PLAY,
		};

		PhysicsState state = STOP;

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