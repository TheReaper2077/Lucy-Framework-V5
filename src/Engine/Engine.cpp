#include "Engine.h"
#include "Window.h"

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
	MeshRenderPass meshrenderpass;

	spriterenderpass.FirstInit();
	spriterenderpass.Init();
	meshrenderpass.FirstInit();
	meshrenderpass.Init();

	lucy::Sprite sprite;

	sprite.texture = new lgl::Texture();
	sprite.texture->Bind();
	sprite.texture->LoadTexture("D:\\C++\\Lucy Framework V5\\assets\\Redstone.PNG");

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
	registry.emplace<lucy::Camera>(camera_entity, true);

	Mesh mesh;

	mesh.positions = {
		{ -0.5, -0.5, -0.5, },
		{ 0.5, -0.5, -0.5, },
		{ 0.5,  0.5, -0.5, },
		{ 0.5,  0.5, -0.5, },
		{ -0.5,  0.5, -0.5, },
		{ -0.5, -0.5, -0.5, },
	};

	mesh.colors = {
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
	};

	mesh.ReCalculateNormals();
	mesh.Transfer();

	auto mesh_entity = registry.create();
	registry.emplace<lucy::Tag>(mesh_entity, "Mesh");
	registry.emplace<lucy::Transform>(mesh_entity, glm::vec3(0, 0, 3));
	registry.emplace<lucy::MeshRenderer>(mesh_entity, &mesh);
	
	CameraSystem camerasystem;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	while (!events.IsQuittable()) {
		events.Update();
		timestep.Update();

		if (events.IsWindowResized()) {
			window.pos = events.GetWindowPos();
			window.size = events.GetWindowSize();
		}

		camerasystem.Update();

		renderer.Clear({ 0, 0, 0, 0 });
		glViewport(0, 0, window.size.x, window.size.y);

		auto& transform = registry.get<Transform>(entity);
		auto& spriterenderer = registry.get<SpriteRenderer>(entity);

		transform.rotation.z += timestep.dt;

		if (transform.rotation.z >= 360) {
			transform.rotation.z = 0;
		}

		spriterenderpass.Render();
		meshrenderpass.Render();

		SDL_GL_SwapWindow(sdl_window);
	}
}

void lucy::Engine::Destroy() {
	SDL_DestroyWindow(sdl_window);
}
