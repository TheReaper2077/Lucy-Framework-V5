#include "SpriteRenderPass.h"

#include <Components/Components.h>

void lucy::SpriteRenderPass::FirstInit() {
	
}

void lucy::SpriteRenderPass::Init() {
	
}

void lucy::SpriteRenderPass::Render() {
	using namespace lucy::Components;

	for (auto [entity, transform, sprite, spriterenderer]: registry.view<Transform, Sprite, SpriteRenderer>().each()) {
		
	}

	for (auto [entity, transform, spriterenderer]: registry.view<Transform, SpriteRenderer>().each()) {

	}

	for (auto [entity, transform, sprite]: registry.view<Transform, Sprite>().each()) {
		
	}
}

