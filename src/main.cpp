#include "Lucy/Engine.h"
#include <Systems/Systems.h>
#include <TestApp/App.h>
#include <Editor/Editor.h>
#include <Editor/EditorSystem.h>

int main(int argcount, char** args) {
	// App
	lucy::Engine::AddInitializationSystem(InitializeApp);
	lucy::Engine::AddRuntimeSystem(UpdateApp);

	// Systems
	lucy::Engine::AddRuntimeSystem(lucy::MainSystems);

	// Editor
	// lucy::Engine::AddInitializationSystem(lucy::Editor::Initialize);
	// lucy::Engine::AddRuntimeSystem(lucy::Editor::Update);

	// lucy::Editor::AddLayer(lucy::System::EditorSystem);

	lucy::Engine::Initialize();
	lucy::Engine::Mainloop();

	// lucy::Editor::ShutDown();
	lucy::Engine::ShutDown();

	return 0;
}