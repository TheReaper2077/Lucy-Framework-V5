#pragma once

#include <vector>
#include <LucyGL/API.h>
#include <glm/glm.hpp>

namespace lucy::Vertex {
	template <typename T>
	std::vector<T>& GetVertices() {
		static std::vector<T> vertices;
		return vertices;
	}

	template <typename T>
	lgl::VertexBuffer* GetVertexBuffer() {
		static lgl::VertexBuffer vertexbuffer;
		return &vertexbuffer;
	}

	#define SET_VERTEXARRAY(...) static lgl::VertexArray* VertexArray() { static lgl::VertexArray vertexarray(__VA_ARGS__); return &vertexarray; }

	enum Index {
		position = 0,
		color,
		normal,
		tex,
		idx,
		uv,

		Index_COUNT
	};

	struct P1;
	struct P1C1;
	struct P1N1;
	struct P1C1N1;
	struct P1UV1;
	struct P1C1UV1;
	struct P1N1UV1;
	struct P1C1N1UV1;
	struct P1I1;
	struct P1C1I1;
	struct P1N1I1;
	struct P1C1N1I1;
	struct P1UV1I1;
	struct P1C1UV1I1;
	struct P1N1UV1I1;
	struct P1C1N1UV1I1;
	struct P1T1;
	struct P1C1T1;
	struct P1N1T1;
	struct P1C1N1T1;
	struct P1UV1T1;
	struct P1C1UV1T1;
	struct P1N1UV1T1;
	struct P1C1N1UV1T1;
	struct P1I1T1;
	struct P1C1I1T1;
	struct P1N1I1T1;
	struct P1C1N1I1T1;
	struct P1UV1I1T1;
	struct P1C1UV1I1T1;
	struct P1N1UV1I1T1;
	struct P1C1N1UV1I1T1;
}

#include "VertexPermutations.h"