#pragma once

#include <LucyGL/LucyGL.h>
#include <memory>
#include <stddef.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace lre::Vertex {
	typedef lgl::VertexArray*(*function)();

	extern std::unordered_map<uint64_t, function> MAP;

	enum Index {
		position,
		color,
		normal,
		tex,
		uv,
		uvw,

		INDEX_COUNT
	};

	struct C1 {
		glm::vec4 color;

		static const uint64_t flag = (1 << Index::color);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1 {
		glm::vec4 color;
		glm::vec3 normal;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1T1 {
		glm::vec4 color;
		glm::vec3 normal;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1UV1 {
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1UV1T1 {
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1UV1UVW1 {
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1UV1UVW1T1 {
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1UVW1 {
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1N1UVW1T1 {
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1T1 {
		glm::vec4 color;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1UV1 {
		glm::vec4 color;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1UV1T1 {
		glm::vec4 color;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1UV1UVW1 {
		glm::vec4 color;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1UV1UVW1T1 {
		glm::vec4 color;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1UVW1 {
		glm::vec4 color;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct C1UVW1T1 {
		glm::vec4 color;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::color) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1 {
		glm::vec3 normal;

		static const uint64_t flag = (1 << Index::normal);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1T1 {
		glm::vec3 normal;
		float tex;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1UV1 {
		glm::vec3 normal;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1UV1T1 {
		glm::vec3 normal;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1UV1UVW1 {
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1UV1UVW1T1 {
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1UVW1 {
		glm::vec3 normal;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct N1UVW1T1 {
		glm::vec3 normal;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct NullVertex {
		

		static const uint64_t flag = 0;

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					
				});

			return instance;
		}
	};

	struct P1 {
		glm::vec3 position;

		static const uint64_t flag = (1 << Index::position);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1 {
		glm::vec3 position;
		glm::vec4 color;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1UV1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1UV1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1UV1UVW1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1UV1UVW1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1UVW1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1N1UVW1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1T1 {
		glm::vec3 position;
		glm::vec4 color;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1UV1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1UV1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1UV1UVW1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1UV1UVW1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1UVW1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1C1UVW1T1 {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::color, 4, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1 {
		glm::vec3 position;
		glm::vec3 normal;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1T1 {
		glm::vec3 position;
		glm::vec3 normal;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1UV1 {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1UV1T1 {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1UV1UVW1 {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1UV1UVW1T1 {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1UVW1 {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1N1UVW1T1 {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::normal, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1T1 {
		glm::vec3 position;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1UV1 {
		glm::vec3 position;
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1UV1T1 {
		glm::vec3 position;
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1UV1UVW1 {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1UV1UVW1T1 {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1UVW1 {
		glm::vec3 position;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct P1UVW1T1 {
		glm::vec3 position;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::position) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::position, 3, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct T1 {
		float tex;

		static const uint64_t flag = (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct UV1 {
		glm::vec2 uv;

		static const uint64_t flag = (1 << Index::uv);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::uv, 2, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct UV1T1 {
		glm::vec2 uv;
		float tex;

		static const uint64_t flag = (1 << Index::uv) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct UV1UVW1 {
		glm::vec2 uv;
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::uv) | (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct UV1UVW1T1 {
		glm::vec2 uv;
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::uv, 2, lgl::FLOAT },
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct UVW1 {
		glm::vec3 uvw;

		static const uint64_t flag = (1 << Index::uvw);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::uvw, 3, lgl::FLOAT },
				});

			return instance;
		}
	};

	struct UVW1T1 {
		glm::vec3 uvw;
		float tex;

		static const uint64_t flag = (1 << Index::uvw) | (1 << Index::tex);

		static lgl::VertexArray* VertexArray() {
			static lgl::VertexArray* instance = nullptr;

			if (instance == nullptr)
				instance = new lgl::VertexArray({
					{ Index::uvw, 3, lgl::FLOAT },
					{ Index::tex, 1, lgl::FLOAT },
				});

			return instance;
		}
	};
}