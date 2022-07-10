#include "Engine.h"
#include "Window.h"

#include "Renderer.h"
#include "SpriteRenderPass.h"
#include <Components/Components.h>
#include <Structures/Structures.h>

#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>

void lucy::Engine::Init() {
	auto null_entity = registry.create();

	auto& window = registry.store<Window>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	sdl_window = SDL_CreateWindow(window.title.c_str(), window.pos.x, window.pos.y, window.size.x, window.size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(sdl_window);

	sdl_context = SDL_GL_CreateContext(sdl_window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
}

void lucy::Engine::Mainloop() {
	auto& timestep = registry.store<TimeStep>();
	auto& events = registry.store<Events>();
	auto& window = registry.store<Window>();
	auto& renderer = registry.store<Renderer>();

	SpriteRenderPass spriterenderpass;

	spriterenderpass.FirstInit();
	spriterenderpass.Init();

	renderer.SetOrtho(0, window.size.x, window.size.y, 0, -1, 1);

	lucy::Sprite sprite;

	sprite.texture = new lgl::Texture();
	sprite.texture->Bind();
	sprite.texture->LoadTexture("D:\\C++\\Lucy Framework V5\\assets\\Redstone.PNG");
	
	auto entity = registry.create();
	registry.emplace<lucy::Tag>(entity, "Entity");
	registry.emplace<lucy::Transform>(entity, glm::vec3(100, 100, 0), glm::vec3(0, 0, 45), glm::vec3(100, 100, 100));
	registry.emplace<lucy::SpriteRenderer>(entity, sprite);

	auto entity2 = registry.create();
	registry.emplace<lucy::Tag>(entity2, "Entity2");
	registry.emplace<lucy::Transform>(entity2, glm::vec3(200, 200, 0), glm::vec3(0, 0, 0), glm::vec3(100, 100, 100));
	registry.emplace<lucy::SpriteRenderer>(entity2);

	auto camera_entity = registry.create();
	registry.emplace<lucy::Tag>(camera_entity, "CameraFPS");
	registry.emplace<lucy::Transform>(camera_entity, glm::vec3(0, 0, 0));
	registry.emplace<lucy::Camera>(camera_entity, true);

	while (!events.IsQuittable()) {
		events.Update();
		timestep.Update();

		if (events.IsWindowResized()) {
			window.pos = events.GetWindowPos();
			window.size = events.GetWindowSize();
		}

		renderer.Clear({ 0, 0, 0, 0 });

		auto& transform = registry.get<Transform>(entity);
		auto& spriterenderer = registry.get<SpriteRenderer>(entity);

		transform.rotation.z += timestep.GetTimeStep();

		if (transform.rotation.z >= 360) {
			transform.rotation.z = 0;
		}

		spriterenderpass.Render();

		SDL_GL_SwapWindow(sdl_window);
	}
}

void lucy::Engine::Destroy() {
	SDL_DestroyWindow(sdl_window);
}
