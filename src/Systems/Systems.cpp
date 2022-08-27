#include "Systems.h"

#include "RenderSystem.h"
#include "CameraSystem.h"

void lucy::MainSystems() {
	System::CameraSystem();
	System::RenderSystem();
}
