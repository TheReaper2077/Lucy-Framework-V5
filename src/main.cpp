#include "Engine/Engine.h"
#include <System/System.h>
#include <Application/Application.h>

int main(int argcount, char** args) {
	lucy::Engine engine;

	engine.AddInitializationSystem(InitApplication);

	engine.AddRuntimeSystem(UpdateApplication);
	engine.AddRuntimeSystem(lucy::System::CameraSystem);
	// engine.AddRuntimeSystem(lucy::System::PhysicsSystem);
	engine.AddRuntimeSystem(lucy::System::RenderSystem);
	engine.AddImGuiSystem(lucy::System::EditorSystemUpdate);

	engine.Init();
	engine.Mainloop();

	return 0;
}