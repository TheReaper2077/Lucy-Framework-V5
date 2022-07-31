#pragma once

#include <Engine/TimeStep.h>
#include <Engine/ECS.h>
#include <Engine/Events.h>

class Application {
	public:
		void Init();
		void Update();
};

void InitGame(lucy::Registry& registry);
void UpdateGame(lucy::Registry& registry);