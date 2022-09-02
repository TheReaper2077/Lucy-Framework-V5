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

void LoadArmModel() {
	auto& meshregistry = registry.store<lucy::MeshRegistry>();

	auto* material = new lucy::Material;
	material->ambient = { 1, 1, 1 };
	material->diffuse = { 1, 1, 1 };
	material->specular = { 0, 0.9, 0.6 };
	material->shininess = 0.9;

	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { -90, 0, 0 };//{ -55.25, -44.0448, -71.6270 };
		lucy::Assets::Load("C:\\Users\\krishnadev\\Documents\\UPPER BASE.stl");

		tag.name = "UPPER BASE";
		meshrenderer.mesh = meshregistry.GetByFilepath("C:\\Users\\krishnadev\\Documents\\UPPER BASE.stl");
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { -90, 0, 0 };//{ -55.25, -44.0448, -71.6270 };
		lucy::Assets::Load("C:\\Users\\krishnadev\\Documents\\LOWER BASE.stl");

		tag.name = "LOWER BASE";
		meshrenderer.mesh = meshregistry.GetByFilepath("C:\\Users\\krishnadev\\Documents\\LOWER BASE.stl");
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { -90, 0, 0 };//{ -55.25, -44.0448, -71.6270 };
		lucy::Assets::Load("C:\\Users\\krishnadev\\Documents\\UPPER ELBOW.stl");

		tag.name = "UPPER ELBOW";
		meshrenderer.mesh = meshregistry.GetByFilepath("C:\\Users\\krishnadev\\Documents\\UPPER ELBOW.stl");
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { -90, 0, 0 };//{ -55.25, -44.0448, -71.6270 };
		lucy::Assets::Load("C:\\Users\\krishnadev\\Documents\\LOWER ELBOW.stl");

		tag.name = "LOWER ELBOW";
		meshrenderer.mesh = meshregistry.GetByFilepath("C:\\Users\\krishnadev\\Documents\\LOWER ELBOW.stl");
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { -90, 0, 0 };//{ -55.25, -44.0448, -71.6270 };
		lucy::Assets::Load("C:\\Users\\krishnadev\\Documents\\ARM.stl");

		tag.name = "ARM";
		meshrenderer.mesh = meshregistry.GetByFilepath("C:\\Users\\krishnadev\\Documents\\ARM.stl");
		meshrenderer.material = material;
	}
}

void InitializeApp() {
	auto& meshregistry = registry.store<lucy::MeshRegistry>();
	auto& engine_state = registry.store<lucy::State>();

	auto [vertexcount, positions, normals, colors, uvs, uvws, indexcount, indices] = lutil::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\cube.obj", "Cube");

	for (int i = 0; i < vertexcount; i++) {
		std::cout << positions[i].x << ' ' << positions[i].y << ' ' << positions[i].z << '\n';
	}

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
	// lucy::Transform* parent = nullptr;
	// {
	// 	auto entity = registry.create();
	// 	auto& tag = registry.emplace<lucy::Tag>(entity);
	// 	auto& transform = registry.emplace<lucy::Transform>(entity);
	// 	auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

	// 	lucy::AssetLoader::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\flat_ico.obj");

	// 	tag.name = "Sphere";
	// 	meshrenderer.mesh = meshregistry.GetByFilepath("D:\\C++\\Lucy Framework V5\\assets\\flat_ico.obj");
	// 	meshrenderer.material = new lucy::Material;
	// 	// parent = &transform;
	// }
	// {
	// 	auto entity = registry.create();
	// 	auto& tag = registry.emplace<lucy::Tag>(entity);
	// 	auto& transform = registry.emplace<lucy::Transform>(entity);
	// 	auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

	// 	transform.translation = { 0, -2, 0 };
	// 	transform.scale = { 1, 1, 1 };

	// 	lucy::AssetLoader::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");

	// 	tag.name = "Cube";
	// 	meshrenderer.mesh = meshregistry.GetByFilepath("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");
	// 	meshrenderer.material = new lucy::Material;
	// 	transform.parent_entity = parent;
	// }
	// {
	// 	auto entity = registry.create();
	// 	auto& tag = registry.emplace<lucy::Tag>(entity);
	// 	auto& transform = registry.emplace<lucy::Transform>(entity);
	// 	auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

	// 	transform.translation = { 0, 2, 0 };
	// 	transform.scale = { 1, 1, 1 };

	// 	lucy::AssetLoader::LoadMesh("D:\\C++\\Lucy Framework V5\\assets\\sphere.obj");

	// 	tag.name = "Smooth Sphere";
	// 	meshrenderer.mesh = meshregistry.GetByFilepath("D:\\C++\\Lucy Framework V5\\assets\\sphere.obj");
	// 	meshrenderer.material = new lucy::Material;
	// }
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& light = registry.emplace<lucy::Light>(entity);

		tag.name = "Light Entity";
		transform.rotation = { -27, -11, -2 };
	}

	LoadArmModel();
}

void UpdateApp() {
	
}
