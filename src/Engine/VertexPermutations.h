#pragma once

#include "Vertex.h"

struct lucy::Vertex::P1 {
	glm::vec3 position;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1 {
	glm::vec3 position;
	glm::vec4 color;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1 {
	glm::vec3 position;
	glm::vec3 normal;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1UV1 {
	glm::vec3 position;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1UV1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1UV1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1UV1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1I1 {
	glm::vec3 position;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1I1 {
	glm::vec3 position;
	glm::vec4 color;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1I1 {
	glm::vec3 position;
	glm::vec3 normal;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1I1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1UV1I1 {
	glm::vec3 position;
	glm::vec2 uv;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1UV1I1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1UV1I1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1UV1I1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	float idx;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1T1 {
	glm::vec3 position;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1T1 {
	glm::vec3 position;
	glm::vec4 color;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1UV1T1 {
	glm::vec3 position;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1UV1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1UV1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1UV1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1I1T1 {
	glm::vec3 position;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1I1T1 {
	glm::vec3 position;
	glm::vec4 color;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1I1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1I1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1UV1I1T1 {
	glm::vec3 position;
	glm::vec2 uv;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1UV1I1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1N1UV1I1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};
struct lucy::Vertex::P1C1N1UV1I1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	float idx;
	float tex;

	SET_VERTEXARRAY({
		{ Index::position, 3, lgl::FLOAT },
		{ Index::color, 4, lgl::FLOAT },
		{ Index::normal, 3, lgl::FLOAT },
		{ Index::uv, 2, lgl::FLOAT },
		{ Index::idx, 1, lgl::FLOAT },
		{ Index::tex, 1, lgl::FLOAT },
	})
};