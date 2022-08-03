#pragma once

#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>
#include <Structures/Structures.h>

namespace lucy {
	struct SpriteRenderer {
		glm::vec4 color = { 1, 1, 1, 0 };
		glm::vec2 uv0 = { 0, 0 };
		glm::vec2 uv1 = { 1, 1 };

		bool visible = true;
		bool enable_lighting = false;
		bool enable_texture = false;
		bool enable_color = true;

		Sprite* sprite = nullptr;
		Material* material = nullptr;

		SpriteRenderer() {}
		SpriteRenderer(const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1): color(color), uv0(uv0), uv1(uv1) {}
		SpriteRenderer(const glm::vec4& color): color(color) {}
		SpriteRenderer(Sprite* sprite): sprite(sprite) {}
		SpriteRenderer(Sprite& sprite): sprite(&sprite) {}
	};
}