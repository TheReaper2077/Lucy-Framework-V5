#pragma once

#include <Editor/EditorCamera.h>
#include <Lucy/Lucy.h>
#include <LucyRE/LucyRE.h>
#include <Lucy/Engine.h>
#include <Structures/Structures.h>
#include <Lucy/Events.h>
#include <Lucy/MeshRegistry.h>
#include <iostream>
#include <LucyUtil/LucyUtil.h>

static auto& registry = lucy::Registry::Instance();
lucy::Entity camera_entity;

void InitializeApp() {
	auto& meshregistry = registry.store<lucy::MeshRegistry>();
	auto& engine_state = registry.store<lucy::State>();

	{
		camera_entity = registry.create();

		auto& tag = registry.emplace<lucy::Tag>(camera_entity);
		auto& transform = registry.emplace<lucy::Transform>(camera_entity);
		auto& camera = registry.emplace<lucy::Camera>(camera_entity);

		tag.name = "Game Camera";

		camera.enable = true;
		camera.view = glm::mat4(1.0f);
		camera.clear_color = { 0, 0, 0, 1 };
		camera.position = { 0, 0, 50 };
		camera.update = lucy::EditorCameraUpdate;

		engine_state.camera_entity = camera_entity;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		lucy::AssetLoader::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\flat_ico.obj");

		tag.name = "Sphere";
		meshrenderer.mesh = meshregistry.GetByFilepath("D:\\C++\\Lucy Framework V5\\assets\\flat_ico.obj");
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.translation = { 0, -2, 0};
		transform.scale = { 100, 1, 100};

		lucy::AssetLoader::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");

		tag.name = "Cube";
		meshrenderer.mesh = meshregistry.GetByFilepath("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");
	}
}

void UpdateApp() {
	
}
