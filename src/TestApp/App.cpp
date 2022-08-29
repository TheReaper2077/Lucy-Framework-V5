#pragma once

#include <Lucy/Lucy.h>
#include <LucyRE/LucyRE.h>
#include <Lucy/Engine.h>
#include <Structures/Structures.h>
#include <Lucy/Events.h>
#include <Lucy/MeshRegistry.h>
#include <iostream>

static auto& registry = lucy::Registry::Instance();
static auto& meshregistry = registry.store<lucy::MeshRegistry>();
lucy::Entity camera_entity;

void InitializeApp() {
	{
		// camera_entity = registry.create();

		// auto& tag = registry.emplace<lucy::Tag>(camera_entity);
		// auto& transform = registry.emplace<lucy::Transform>(camera_entity);
		// auto& camera = registry.emplace<lucy::Camera>(camera_entity);

		// tag.name = "Camera Entity";

		// camera.enable = true;
		// camera.projection_type = lucy::PERSPECTIVE;
		// camera.view = glm::mat4(1.0f);
		// // camera.projection = glm::mat4(1.0f);
		// camera.view_mode = lucy::ViewMode_Editor;
		// transform.translation = { 0, 0, 1 };
		// camera.clear_color = { 1, 1, 0, 1 };
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		lucy::AssetLoader::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");

		tag.name = "Mesh Entity";
		meshrenderer.mesh = meshregistry.GetByFilepath("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");
	}
}

void UpdateApp() {
	
}
