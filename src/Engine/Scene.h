#pragma once

#include <Engine/ECS.h>
#include <unordered_map>

namespace lucy {
	class Scene {
		enum GameState {
			PLAY,
			PAUSE,
			STOP,
		};

		Entity camera_entity;

		std::unordered_set<Entity> permanent_entities, temporary_entities;

		std::string filename;

		bool enable_physics;
		GameState game_state = STOP;

	public:
		Entity CreateEntity(std::string name);
		Entity CreateCameraEntity(std::string name);
		Entity CreateMeshEntity(std::string name);
		Entity CreateSpriteEntity(std::string name);
		Entity CreateRigidbody2DEntity(std::string name);

		void SaveAs(std::string filename);
		void Load(std::string filename);
		void Save();
		void ReLoad();

		void Play();
		void Pause();
		void Stop();

		bool IsPlaying();
		bool IsPaused();
		bool IsStopped();
	};
};