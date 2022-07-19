#pragma once

#include <string>
#include "ECS.h"

namespace lucy {
	struct Functions {
	private:
		std::string GetName(std::string name);

		bool playing = false;
		bool paused = false;

	public:
		Entity CreateEmptyEntity();
		Entity CreateLightEntity();
		Entity CreateCameraEntity();
		Entity CreateMeshEntity();
		Entity CreateSpriteEntity();

		void Serialize();
		void Deserialize();
		void SerializeEntities();
		void DeserializeEntities();

		void StartPlaying();
		void StopPlaying();
		void PausePlaying();
		bool IsPlaying();
		bool IsPlayingPaused();

		bool IsPhysicsEnabled();
		void SetPhysicsStatus(bool status);
	};
}