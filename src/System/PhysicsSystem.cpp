#include "PhysicsSystem.h"
#include <box2d/b2_api.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_shape.h>
#include <box2d/box2d.h>
#include <Components/Components.h>
#include <Engine/TimeStep.h>
#include <Engine/Functions.h>
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

static lucy::Registry cache_registry;

void lucy::System::PhysicsSystem(Registry& registry) {
	auto& timestep = registry.store<TimeStep>();
	auto& events = registry.store<Events>();
	auto& functions = registry.store<Functions>();

	if (world == nullptr && functions.IsPhysicsPlaying()) {
		world = new b2World({ 0.0f, -9.8f });

		if (functions.enable_physics_caching) {
			for (auto entity: registry.view<Tag, Transform>()) {
				auto [
					tag, transform, rb2d, bc2d, spriterenderer, meshrenderer, light, camera
				] = registry.try_get<Tag, Transform, Rigidbody2D, BoxCollider2D, SpriteRenderer, MeshRenderer, Light, Camera>(entity);

				auto cache_entity = cache_registry.create();
				cache_registry.emplace<Entity>(cache_entity, entity);

				if (tag != nullptr)
					cache_registry.emplace<Tag>(cache_entity, *tag);
				if (transform != nullptr)
					cache_registry.emplace<Transform>(cache_entity, *transform);
				if (rb2d != nullptr)
					cache_registry.emplace<Rigidbody2D>(cache_entity, *rb2d);
				if (bc2d != nullptr)
					cache_registry.emplace<BoxCollider2D>(cache_entity, *bc2d);
				if (spriterenderer != nullptr)
					cache_registry.emplace<SpriteRenderer>(cache_entity, *spriterenderer);
				if (meshrenderer != nullptr)
					cache_registry.emplace<MeshRenderer>(cache_entity, *meshrenderer);
				if (camera != nullptr)
					cache_registry.emplace<Camera>(cache_entity, *camera);
				if (light != nullptr)
					cache_registry.emplace<Light>(cache_entity, *light);
			}
		}
	}

	if (world != nullptr && functions.IsPhysicsPlaying()) {
		// Runtime Physics Logic

		world->Step(timestep.dt, functions.velocity_iterations, functions.position_iterations);

		for (auto [entity, transform, rigidbody2D]: registry.view<Transform, Rigidbody2D>().each()) {
			b2Body* body = (b2Body*)rigidbody2D.runtime_body;

			if (body == nullptr) {
				b2BodyDef body_def;

				body_def.type = LucyTypeToB2DType(rigidbody2D.type);
				body_def.position.Set(transform.translation.x, transform.translation.y);
				body_def.angle = transform.rotation.z;

				body = world->CreateBody(&body_def);
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

			const auto& position = body->GetPosition();

			// body->ApplyForce({ rigidbody2D.force.x, rigidbody2D.force.y }, { position.x, position.y }, false);

			transform.translation.x = position.x;
			transform.translation.y = position.y;
			transform.rotation.z = body->GetAngle() * 180 / 3.141592653589793238;
		}
	}

	if (functions.IsPhysicsStopped()) {
		free(world);
		world = nullptr;

		if (functions.enable_physics_caching) {
			for (auto cache_entity: cache_registry.view<Entity, Tag, Transform>()) {
				auto [
					tag, transform, rb2d, bc2d, spriterenderer, meshrenderer, light, camera
				] = cache_registry.try_get<Tag, Transform, Rigidbody2D, BoxCollider2D, SpriteRenderer, MeshRenderer, Light, Camera>(cache_entity);

				const auto& entity = cache_registry.get<Entity>(cache_entity);

				if (tag != nullptr) {
					registry.remove<Tag>(entity);
					registry.emplace<Tag>(entity, *tag);
				}
				if (transform != nullptr) {
					registry.remove<Transform>(entity);
					registry.emplace<Transform>(entity, *transform);
				}
				if (rb2d != nullptr) {
					registry.remove<Rigidbody2D>(entity);
					registry.emplace<Rigidbody2D>(entity, *rb2d);
				}
				if (bc2d != nullptr) {
					registry.remove<BoxCollider2D>(entity);
					registry.emplace<BoxCollider2D>(entity, *bc2d);
				}
				if (spriterenderer != nullptr) {
					registry.remove<SpriteRenderer>(entity);
					registry.emplace<SpriteRenderer>(entity, *spriterenderer);
				}
				if (meshrenderer != nullptr) {
					registry.remove<MeshRenderer>(entity);
					registry.emplace<MeshRenderer>(entity, *meshrenderer);
				}
				if (camera != nullptr) {
					registry.remove<Camera>(entity);
					registry.emplace<Camera>(entity, *camera);
				}
				if (light != nullptr) {
					registry.remove<Light>(entity);
					registry.emplace<Light>(entity, *light);
				}
			}

			cache_registry.clear();
		}
	}
}