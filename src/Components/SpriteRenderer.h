#pragma once

#include <LucyGL/API.h>
#include <glm/glm.hpp>
#include <Structures/Structures.h>

namespace lucy::Components {
	struct SpriteRenderer {
		glm::vec4 color = glm::vec4(1, 1, 1, 1);
		glm::vec2 uv0 = glm::vec2(0, 0);
		glm::vec2 uv1 = glm::vec2(1, 1);

		bool enable_lighting = false;
		bool enable_texture = false;
		bool enable_color = false;

		Sprite* sprite = nullptr;

		SpriteRenderer() {}
		SpriteRenderer(const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1): color(color), uv0(uv0), uv1(uv1) {}
		SpriteRenderer(const glm::vec4& color): color(color) {}
		SpriteRenderer(Sprite* sprite): sprite(sprite) {}
		SpriteRenderer(Sprite& sprite): sprite(&sprite) {}
	};
}