#include "Engine/Engine.h"
#include <System/System.h>
#include <Application/Application.h>

int main(int argcount, char** args) {
	lucy::Engine engine;

	engine.AddInitializationSystem(InitApplication);
	engine.AddInitializationSystem(lucy::System::EditorSystemInitialize);

	engine.AddRuntimeSystem(UpdateApplication);
	engine.AddRuntimeSystem(lucy::System::CameraSystem);
	// engine.AddRuntimeSystem(lucy::System::PhysicsSystem);
	engine.AddRuntimeSystem(lucy::System::RenderSystem);
	engine.AddRuntimeSystem(lucy::System::EditorSystemUpdate);

	engine.Init();
	engine.Mainloop();

	return 0;
}