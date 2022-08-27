#pragma once

#include <LucyRE/LucyRE.h>
#include <Lucy/Engine.h>
#include <Structures/Structures.h>
#include <Lucy/Events.h>

static auto& registry = lucy::Registry::Instance();
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
}

void UpdateApp() {
	
}
