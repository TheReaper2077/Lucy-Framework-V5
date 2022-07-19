#include "Engine.h"
#include "Window.h"

#include <Registry/Registry.h>
#include "Renderer.h"
#include "SpriteRenderPass.h"
#include "MeshRenderPass.h"
#include <Components/Components.h>
#include <Structures/Structures.h>
#include <System/CameraSystem.h>

#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include <Editor/Editor.h>

static lucy::Editor editor;

void lucy::Engine::Init() {
	auto null_entity = registry.create();
	auto& renderer = registry.store<Renderer>();
	auto& events = registry.store<Events>();
	auto* window = registry.store<WindowRegistry>()[MAIN_WINDOW];
	auto& meshregistry = registry.store<MeshRegistry>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	sdl_window = SDL_CreateWindow(window->title.c_str(), window->pos.x, window->pos.y, window->size.x, window->size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(sdl_window);

	sdl_glcontext = SDL_GL_CreateContext(sdl_window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	events.Init();
	renderer.Init();
	editor.Init(sdl_window, &sdl_glcontext);
	meshregistry.Init();

	renderer.AddRenderPass<SpriteRenderPass>();
	renderer.AddRenderPass<MeshRenderPass>();
}

void lucy::Engine::Mainloop() {
	auto& timestep = registry.store<TimeStep>();
	auto& events = registry.store<Events>();
	auto& windowregistry = registry.store<WindowRegistry>();
	auto* window = windowregistry[MAIN_WINDOW];
	auto& renderer = registry.store<Renderer>();
	auto& meshregistry = registry.store<MeshRegistry>();
	auto& spriteregistry = registry.store<SpriteRegistry>();
	auto& materialregistry = registry.store<MaterialRegistry>();

	lucy::Sprite sprite;

	sprite.texture_raw = spriteregistry.GetTexture("D:\\C++\\Lucy Framework V5\\assets\\Redstone.PNG");

	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, "Entity");
	registry.emplace<lucy::Transform>(entity, glm::vec3(0, 0, -1), glm::vec3(0, 0, 45), glm::vec3(1, 1, 1));
	registry.emplace<lucy::SpriteRenderer>(entity, sprite);

	auto entity2 = registry.create();
	registry.emplace<lucy::Tag>(entity2, "Entity2");
	registry.emplace<lucy::Transform>(entity2, glm::vec3(1, 1, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	registry.emplace<lucy::SpriteRenderer>(entity2);

	auto camera_entity = registry.create();
	registry.emplace<lucy::Tag>(camera_entity, "CameraFPS");
	registry.emplace<lucy::Transform>(camera_entity, glm::vec3(0, 0, 1));
	registry.emplace<lucy::Camera>(camera_entity, ViewMode_FPS, true);

	auto* mesh = meshregistry.GetMesh("test");

	Material material;

	materialregistry.AddMaterial(material);

	auto mesh_entity = registry.create();
	registry.emplace<lucy::Tag>(mesh_entity, "Mesh");
	registry.emplace<lucy::Transform>(mesh_entity, glm::vec3(0, -4, 0), glm::vec3(0, 0, 0));
	registry.emplace<lucy::MeshRenderer>(mesh_entity, mesh);

	auto mesh_entity2 = registry.create();
	registry.emplace<lucy::Tag>(mesh_entity2, "Mesh2");
	registry.emplace<lucy::Transform>(mesh_entity2, glm::vec3(0, 0, 3), glm::vec3(0, 0, 0));
	registry.emplace<lucy::MeshRenderer>(mesh_entity2, mesh, &material);

	auto light_entity = registry.create();
	registry.emplace<lucy::Tag>(light_entity, "light");
	registry.emplace<lucy::Transform>(light_entity, glm::vec3(0, 0, 3), glm::vec3(0, 90, 0));
	registry.emplace<lucy::Light>(light_entity, lucy::LightMode::POINT_LIGHT);
	CameraSystem camerasystem;

	while (!events.IsQuittable()) {
		events.Update();

		timestep.Update();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);

		camerasystem.Update();

		renderer.RenderMain();

		editor.Render();

		SDL_GL_SwapWindow(sdl_window);
	}
}

void lucy::Engine::Destroy() {
	SDL_DestroyWindow(sdl_window);
}
