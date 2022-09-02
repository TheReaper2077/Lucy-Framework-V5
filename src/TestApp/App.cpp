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


	glm::vec3 lower_base = { 55.25, 44.0448, 71.6270 };	// CENTER
	glm::vec3 lower_elbow = { 55.25, 44.2948, 86.6948 };
	glm::vec3 upper_elbow = { 55.2500, 44.2948, 190.8709 };
	glm::vec3 arm = { 55.2500, 43.2270, 285.2090 };
	{	// STATIC
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { 0, 0, 0 };

		tag.name = "LOWER BASE";
		meshrenderer.mesh = new lucy::Mesh("C:\\Users\\krishnadev\\Documents\\LOWER BASE.stl", "", -lower_base);
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { 0, 0, 0 };

		tag.name = "UPPER BASE";
		meshrenderer.mesh = new lucy::Mesh("C:\\Users\\krishnadev\\Documents\\UPPER BASE.stl", "", -lower_base);
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { 0, 0, 0 };
		transform.translation = upper_elbow - lower_base;

		tag.name = "UPPER ELBOW";
		meshrenderer.mesh = new lucy::Mesh("C:\\Users\\krishnadev\\Documents\\UPPER ELBOW.stl", "", -upper_elbow);
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { 0, 0, 0 };
		transform.translation = lower_elbow - lower_base;

		tag.name = "LOWER ELBOW";
		meshrenderer.mesh = new lucy::Mesh("C:\\Users\\krishnadev\\Documents\\LOWER ELBOW.stl", "", -lower_elbow);
		meshrenderer.material = material;
	}
	{
		auto entity = registry.create();
		auto& tag = registry.emplace<lucy::Tag>(entity);
		auto& transform = registry.emplace<lucy::Transform>(entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		transform.rotation = { 0, 0, 0 };
		transform.translation = arm - lower_base;

		tag.name = "ARM";
		meshrenderer.mesh = new lucy::Mesh("C:\\Users\\krishnadev\\Documents\\ARM.stl", "", -arm);
		meshrenderer.material = material;
	}
}

void InitializeApp() {
	auto& meshregistry = registry.store<lucy::MeshRegistry>();
	auto& engine_state = registry.store<lucy::State>();

	// static lucy::Mesh* mesh = new lucy::Mesh;
	// mesh->Load("D:\\C++\\Lucy Framework V5\\assets\\cube.obj", "Cube");

	{
		// auto entity = registry.create();
		// auto& tag = registry.emplace<lucy::Tag>(entity);
		// auto& transform = registry.emplace<lucy::Transform>(entity);
		// auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(entity);

		// transform.translation = { 0, 0, 0 };
		// transform.scale = { 1, 1, 1 };

		// tag.name = "Cube";
		// meshrenderer.mesh = mesh;
		// meshrenderer.material = new lucy::Material;
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
