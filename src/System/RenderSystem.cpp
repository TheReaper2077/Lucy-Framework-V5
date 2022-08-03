#include "RenderSystem.h"
#include <Engine/Window.h>
#include <LucyRE/LucyRE.h>
#include <Components/Components.h>
#include <glad/glad.h>
#include <Engine/EngineState.h>
#include "MainRenderer.h"

lucy::MainRenderer mainrenderer;

void lucy::System::RenderSystem(Registry& registry) {
	mainrenderer.Render(registry);
}
