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
		textureid,

		uv0,
		uv1,
		uv2,
		uv3,
		uv4,
		uv5,
		uv6,
		uv7,

		uvw0,
		uvw1,
		uvw2,
		uvw3,
		uvw4,
		uvw5,
		uvw6,
		uvw7,

		Index_COUNT
	};

	struct P1 {
		glm::vec3 position;

		SET_VERTEXARRAY({
			{ Index::position, 3, lgl::FLOAT },
		})
	};


	struct P1C1 {
		glm::vec3 position;
		glm::vec4 color;
		
		SET_VERTEXARRAY({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
		})
	};


	struct P1UV1 {
		glm::vec3 position;
		glm::vec2 uv;

		SET_VERTEXARRAY({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uv0, 2, lgl::FLOAT },
		})
	};

	struct P1C1UV1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
	
		SET_VERTEXARRAY({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uv0, 2, lgl::FLOAT },
		})
	};

	struct P1UV1T1 {
		glm::vec3 position;
		glm::vec2 uv;
		float id;

		SET_VERTEXARRAY({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uv0, 2, lgl::FLOAT },
			{ Index::textureid, 1, lgl::FLOAT },
		})
	};

	struct P1C1UV1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
		float id;

		SET_VERTEXARRAY({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uv0, 2, lgl::FLOAT },
			{ Index::textureid, 1, lgl::FLOAT },
		})
	};
}