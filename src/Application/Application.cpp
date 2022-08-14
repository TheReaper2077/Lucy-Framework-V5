#include "Application.h"
#include "SerialPort.h"
#include <Registry/Registry.h>
#include <Components/Components.h>
#include <iostream>
#include <Engine/Functions.h>
#include <fstream>
#include <glm/gtx/string_cast.hpp>

#define PI 3.14159265359

char command[] = "r";

lucy::Entity mesh_entity, camera_entity, sprite_entity;

char output[MAX_DATA_LENGTH], incoming[MAX_DATA_LENGTH];
char port[] = "\\\\.\\COM3";

SerialPort* arduino = nullptr;

void InitApplication(lucy::Registry& registry) {
	arduino = new SerialPort(port);

	if (arduino->isConnected())
		std::cout << "Ardunio Connection Established\n";
	else
		std::cout << "Error Unable to Establish Connection\n";

	auto& timestep = registry.store<lucy::TimeStep>();
	auto& events = registry.store<lucy::Events>();
	auto& meshregistry = registry.store<lucy::MeshRegistry>();
	auto& assetloader = registry.store<lucy::AssetLoader>();
	auto& spriteregistry = registry.store<lucy::SpriteRegistry>();
	auto& materialregistry = registry.store<lucy::MaterialRegistry>();
	auto& functions = registry.store<lucy::Functions>();
	auto& window = registry.store<lucy::Window>();

	lucy::MeshBuilder mesh_builder;

	mesh_builder.primitive = lgl::TRIANGLE;

	mesh_builder.positions = {
		{ -0.5, -0.5, -0.5 },
		{ -0.5, +0.5, -0.5 },
		{ +0.5, +0.5, -0.5 },
		{ +0.5, -0.5, -0.5 },

		{ -0.5, -0.5, +0.5 },
		{ -0.5, +0.5, +0.5 },
		{ +0.5, +0.5, +0.5 },
		{ +0.5, -0.5, +0.5 },

		{ -0.5, -0.5, +0.5 },
		{ -0.5, +0.5, +0.5 },
		{ -0.5, +0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },

		{ +0.5, -0.5, +0.5 },
		{ +0.5, +0.5, +0.5 },
		{ +0.5, +0.5, -0.5 },
		{ +0.5, -0.5, -0.5 },
		
		{ -0.5, -0.5, -0.5 },
		{ -0.5, -0.5, +0.5 },
		{ +0.5, -0.5, +0.5 },
		{ +0.5, -0.5, -0.5 },

		{ -0.5, +0.5, -0.5 },
		{ -0.5, +0.5, +0.5 },
		{ +0.5, +0.5, +0.5 },
		{ +0.5, +0.5, -0.5 },
	};

	mesh_builder.normals = {
		{ 0.0, 0.0, -1.0 },
		{ 0.0, 0.0, -1.0 },
		{ 0.0, 0.0, -1.0 },
		{ 0.0, 0.0, -1.0 },
		
		{ 0.0, 0.0, +1.0 },
		{ 0.0, 0.0, +1.0 },
		{ 0.0, 0.0, +1.0 },
		{ 0.0, 0.0, +1.0 },
		
		{ -1.0, 0.0, 0.0 },
		{ -1.0, 0.0, 0.0 },
		{ -1.0, 0.0, 0.0 },
		{ -1.0, 0.0, 0.0 },
		
		{ +1.0, 0.0, 0.0 },
		{ +1.0, 0.0, 0.0 },
		{ +1.0, 0.0, 0.0 },
		{ +1.0, 0.0, 0.0 },
		
		{ 0.0, -1.0, 0.0 },
		{ 0.0, -1.0, 0.0 },
		{ 0.0, -1.0, 0.0 },
		{ 0.0, -1.0, 0.0 },
		
		{ 0.0, +1.0, 0.0 },
		{ 0.0, +1.0, 0.0 },
		{ 0.0, +1.0, 0.0 },
		{ 0.0, +1.0, 0.0 },		
	};

	mesh_builder.indices = {
		0 + 4*0, 1 + 4*0, 2 + 4*0, 2 + 4*0, 3 + 4*0, 0 + 4*0,
		0 + 4*1, 1 + 4*1, 2 + 4*1, 2 + 4*1, 3 + 4*1, 0 + 4*1,
		0 + 4*2, 1 + 4*2, 2 + 4*2, 2 + 4*2, 3 + 4*2, 0 + 4*2,
		0 + 4*3, 1 + 4*3, 2 + 4*3, 2 + 4*3, 3 + 4*3, 0 + 4*3,
		0 + 4*4, 1 + 4*4, 2 + 4*4, 2 + 4*4, 3 + 4*4, 0 + 4*4,
		0 + 4*5, 1 + 4*5, 2 + 4*5, 2 + 4*5, 3 + 4*5, 0 + 4*5,
	};

	mesh_builder.Transfer();

	assetloader.Import("D:\\C++\\Lucy Framework V5\\assets\\cube.obj");

	mesh_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(mesh_entity, "Mesh Entity");
		registry.emplace<lucy::Transform>(mesh_entity);
		auto& meshrenderer = registry.emplace<lucy::MeshRenderer>(mesh_entity);

		meshrenderer.material = nullptr;
		meshrenderer.mesh = mesh_builder.mesh;
		meshrenderer.enable_lighting = true;
		meshrenderer.visible = true;
	}

	auto light_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(light_entity, "Light Entity");
		registry.emplace<lucy::Transform>(light_entity);
		registry.emplace<lucy::Light>(light_entity);
	}

	auto camera_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(camera_entity, "Camera Entity");
		registry.emplace<lucy::Transform>(camera_entity);
		auto& camera = registry.emplace<lucy::Camera>(camera_entity);

		camera.enable = true;
		camera.type = lucy::PERSPECTIVE;
		camera.mode = lucy::ViewMode_FPS;
		camera.width = window.size.x;
		camera.height = window.size.y;
		functions.main_camera = camera_entity;
		camera.clear_color = { 1, 1, 0, 1 };
	}

	sprite_entity = registry.create();
	{
		registry.emplace<lucy::Tag>(sprite_entity, "Sprite Entity");
		registry.emplace<lucy::Transform>(sprite_entity);
		auto& spriterenderer = registry.emplace<lucy::SpriteRenderer>(sprite_entity);

		spriterenderer.color = { 0, 0, 1, 1 };
	}

	if (arduino->isConnected())
		arduino->writeSerialPort(command, 1);
}

float data[3];

void UpdateApplication(lucy::Registry& registry) {
	auto& functions = registry.store<lucy::Functions>();
	auto& events = registry.store<lucy::Events>();

	auto& sprite_transform = registry.get<lucy::Transform>(sprite_entity);

	if (arduino->isConnected()) {
		bool init = false;
		while (true) {
			auto size = arduino->readSerialPort(output, MAX_DATA_LENGTH);

			if (size > 0) {
				init = true;

				std::cout.write(output, size);
				std::cout << "| - " << size << '\n';

				glm::quat q;

				// ((uint8_t*)&q.w)[0] = output[2];
				// ((uint8_t*)&q.w)[1] = output[3];
				// ((uint8_t*)&q.w)[2] = output[4];
				// ((uint8_t*)&q.w)[3] = output[5];
				
				// ((uint8_t*)&q.x)[0] = output[6];
				// ((uint8_t*)&q.x)[1] = output[7];
				// ((uint8_t*)&q.x)[2] = output[8];
				// ((uint8_t*)&q.x)[3] = output[9];

				// ((uint8_t*)&q.y)[0] = output[10];
				// ((uint8_t*)&q.y)[1] = output[11];
				// ((uint8_t*)&q.y)[2] = output[12];
				// ((uint8_t*)&q.y)[3] = output[13];
				
				// ((uint8_t*)&q.z)[0] = output[14];
				// ((uint8_t*)&q.z)[1] = output[15];
				// ((uint8_t*)&q.z)[2] = output[16];
				// ((uint8_t*)&q.z)[3] = output[17];

				q[0] = ((output[2] << 8) | output[3]) / 16384.0f;
                q[1] = ((output[4] << 8) | output[5]) / 16384.0f;
                q[2] = ((output[6] << 8) | output[7]) / 16384.0f;
                q[3] = ((output[8] << 8) | output[9]) / 16384.0f;
                for (int i = 0; i < 4; i++)
					if (q[i] >= 2) q[i] = -4 + q[i];

				glm::vec3 norm = glm::normalize(q * glm::vec3(1, 0, 0));

				std::cout << glm::to_string(norm) << '\n';

				// sprite_transform.rotation = { atan2(norm.x, norm.z), asin(-norm.y),  };
			} else {
				if (init)
					std::cout << "\n\nend\n\n";
				init = false;

				break;
			}
		}
	}
}
