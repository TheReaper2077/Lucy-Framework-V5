#include "Engine/Engine.h"
#include <System/System.h>
#include <Application/Application.h>

int main(int argcount, char** args) {
	lucy::Engine engine;

	engine.AddRuntimeSystem(lucy::System::CameraSystem);
	engine.AddRuntimeSystem(lucy::System::RenderSystem);
	// engine.AddRuntimeSystem(UpdateGame);

	engine.AddInitializationSystem(InitGame);

	engine.Init();
	engine.Mainloop();

	return 0;
}