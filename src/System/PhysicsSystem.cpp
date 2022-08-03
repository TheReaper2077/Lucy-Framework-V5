#include "PhysicsSystem.h"
#include <box2d/b2_api.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_shape.h>
#include <box2d/box2d.h>
#include <Components/Components.h>
#include <Engine/TimeStep.h>
#include <Engine/Events.h>
#include <iostream>
#include <glm/glm.hpp>

static b2World* world = nullptr;

b2BodyType LucyTypeToB2DType(lucy::BodyType type) {
	switch (type) {
		case lucy::STATIC:	
			return b2BodyType::b2_staticBody;
		case lucy::DYNAMIC:
			return b2BodyType::b2_dynamicBody;
		case lucy::KINEMATIC:
			return b2BodyType::b2_kinematicBody;
	}
}

void lucy::System::PhysicsSystem(Registry& registry) {
	auto& timestep = registry.store<TimeStep>();
	auto& events = registry.store<Events>();

	static bool init = false;

	if (events.IsKeyPressed(SDL_SCANCODE_P)) {
		init = true;
	}

	if (world == nullptr && init) {
		world = new b2World({ 0.0f, -9.8f });

		for (auto [entity, transform, rigidbody2D]: registry.view<Transform, Rigidbody2D>().each()) {
			b2BodyDef body_def;

			body_def.type = LucyTypeToB2DType(rigidbody2D.type);
			body_def.position.Set(transform.translation.x, transform.translation.y);
			body_def.angle = transform.rotation.z;

			b2Body* body = world->CreateBody(&body_def);
			body->SetFixedRotation(rigidbody2D.fixed_rotation);

			rigidbody2D.runtime_body = (void*)body;
			auto* boxcollider2D = registry.try_get<BoxCollider2D>(entity);
			if (boxcollider2D != nullptr) {
				b2PolygonShape poly_shape;
				poly_shape.SetAsBox(transform.scale.x, transform.scale.y);

				b2FixtureDef fixture_def;
				fixture_def.shape = &poly_shape;
				fixture_def.density = boxcollider2D->density;
				fixture_def.friction = boxcollider2D->friction;
				fixture_def.restitution = boxcollider2D->restitution;
				fixture_def.restitutionThreshold = boxcollider2D->restitution_threshold;

				body->CreateFixture(&fixture_def);
			}
		}
	}

	if (world != nullptr) {
		// Runtime Physics Logic
		const int32_t velocity_iterations = 6;
		const int32_t position_iterations = 2;

		world->Step(timestep.dt, velocity_iterations, position_iterations);

		for (auto [entity, transform, rigidbody2D]: registry.view<Transform, Rigidbody2D>().each()) {
			b2Body* body = (b2Body*)rigidbody2D.runtime_body;
			const auto& position = body->GetPosition();

			// body->ApplyForce({ rigidbody2D.force.x, rigidbody2D.force.y }, );

			transform.translation.x = position.x;
			transform.translation.y = position.y;
			transform.rotation.z = body->GetAngle() * 180 / 3.141592653589793238;
		}
	}
}