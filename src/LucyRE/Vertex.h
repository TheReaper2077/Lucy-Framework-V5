#pragma once

#include <LucyGL/LucyGL.h>
#include <memory>
#include <stddef.h>

namespace lre {
	enum Index {
		position = 0,
		color,
		normal,
		uv,
		uvw,
		tex,

		INDEX_COUNT
	};

	struct C1;
	struct C1N1;
	struct C1N1T1;
	struct C1N1UV1;
	struct C1N1UV1T1;
	struct C1N1UV1UVW1;
	struct C1N1UV1UVW1T1;
	struct C1N1UVW1;
	struct C1N1UVW1T1;
	struct C1T1;
	struct C1UV1;
	struct C1UV1T1;
	struct C1UV1UVW1;
	struct C1UV1UVW1T1;
	struct C1UVW1;
	struct C1UVW1T1;
	struct N1;
	struct N1T1;
	struct N1UV1;
	struct N1UV1T1;
	struct N1UV1UVW1;
	struct N1UV1UVW1T1;
	struct N1UVW1;
	struct N1UVW1T1;
	struct P1;
	struct P1C1;
	struct P1C1N1;
	struct P1C1N1T1;
	struct P1C1N1UV1;
	struct P1C1N1UV1T1;
	struct P1C1N1UV1UVW1;
	struct P1C1N1UV1UVW1T1;
	struct P1C1N1UVW1;
	struct P1C1N1UVW1T1;
	struct P1C1T1;
	struct P1C1UV1;
	struct P1C1UV1T1;
	struct P1C1UV1UVW1;
	struct P1C1UV1UVW1T1;
	struct P1C1UVW1;
	struct P1C1UVW1T1;
	struct P1N1;
	struct P1N1T1;
	struct P1N1UV1;
	struct P1N1UV1T1;
	struct P1N1UV1UVW1;
	struct P1N1UV1UVW1T1;
	struct P1N1UVW1;
	struct P1N1UVW1T1;
	struct P1T1;
	struct P1UV1;
	struct P1UV1T1;
	struct P1UV1UVW1;
	struct P1UV1UVW1T1;
	struct P1UVW1;
	struct P1UVW1T1;
	struct T1;
	struct UV1;
	struct UV1T1;
	struct UV1UVW1;
	struct UV1UVW1T1;
	struct UVW1;
	struct UVW1T1;
}


struct lre::P1 {
	glm::vec3 position;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position);
};

struct lre::P1C1 {
	glm::vec3 position;
	glm::vec4 color;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color);
};

struct lre::P1C1N1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal);
};

struct lre::P1C1N1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::tex);
};

struct lre::P1C1N1UV1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv);
};

struct lre::P1C1N1UV1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex);
};

struct lre::P1C1N1UV1UVW1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw);
};

struct lre::P1C1N1UV1UVW1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1C1N1UVW1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw);
};

struct lre::P1C1N1UVW1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1C1T1 {
	glm::vec3 position;
	glm::vec4 color;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::tex);
};

struct lre::P1C1UV1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv);
};

struct lre::P1C1UV1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::tex);
};

struct lre::P1C1UV1UVW1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw);
};

struct lre::P1C1UV1UVW1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1C1UVW1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uvw);
};

struct lre::P1C1UVW1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::color, 4, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::color) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1N1 {
	glm::vec3 position;
	glm::vec3 normal;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal);
};

struct lre::P1N1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::tex);
};

struct lre::P1N1UV1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv);
};

struct lre::P1N1UV1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex);
};

struct lre::P1N1UV1UVW1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw);
};

struct lre::P1N1UV1UVW1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1N1UVW1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uvw);
};

struct lre::P1N1UVW1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::normal, 3, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1T1 {
	glm::vec3 position;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::tex);
};

struct lre::P1UV1 {
	glm::vec3 position;
	glm::vec2 uv;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::uv);
};

struct lre::P1UV1T1 {
	glm::vec3 position;
	glm::vec2 uv;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::uv) | (1 << Index::tex);
};

struct lre::P1UV1UVW1 {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::uv) | (1 << Index::uvw);
};

struct lre::P1UV1UVW1T1 {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uv, 2, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex);
};

struct lre::P1UVW1 {
	glm::vec3 position;
	glm::vec3 uvw;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::uvw);
};

struct lre::P1UVW1T1 {
	glm::vec3 position;
	glm::vec3 uvw;
	float tex;

	static lgl::VertexArray* VertexArray() {
		static lgl::VertexArray* instance = new lgl::VertexArray({
			{ Index::position, 3, lgl::FLOAT },
			{ Index::uvw, 3, lgl::FLOAT },
			{ Index::tex, 1, lgl::FLOAT },
		});

		return instance;
	}

	static const uint64_t flag = (1 << Index::position) | (1 << Index::uvw) | (1 << Index::tex);
};
