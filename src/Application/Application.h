#pragma once

#include <Engine/TimeStep.h>
#include <Engine/ECS.h>
#include <Engine/Events.h>

class Application {
	public:
		void Init();
		void Update();
};

void InitApplication(lucy::Registry& registry);
void UpdateApplication(lucy::Registry& registry);