#include "Vertex.h"

namespace lre::Vertex {
	std::unordered_map<uint64_t, function> MAP = {
		{ (1 << Index::color), C1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal), C1N1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::tex), C1N1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv), C1N1UV1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex), C1N1UV1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw), C1N1UV1UVW1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), C1N1UV1UVW1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw), C1N1UVW1::VertexArray },
		{ (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex), C1N1UVW1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::tex), C1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::uv), C1UV1::VertexArray },
		{ (1 << Index::color) | (1 << Index::uv) | (1 << Index::tex), C1UV1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw), C1UV1UVW1::VertexArray },
		{ (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), C1UV1UVW1T1::VertexArray },
		{ (1 << Index::color) | (1 << Index::uvw), C1UVW1::VertexArray },
		{ (1 << Index::color) | (1 << Index::uvw) | (1 << Index::tex), C1UVW1T1::VertexArray },
		{ (1 << Index::normal), N1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::tex), N1T1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::uv), N1UV1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex), N1UV1T1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw), N1UV1UVW1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), N1UV1UVW1T1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::uvw), N1UVW1::VertexArray },
		{ (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex), N1UVW1T1::VertexArray },
		{ 0, NullVertex::VertexArray },
		{ (1 << Index::position), P1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color), P1C1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal), P1C1N1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::tex), P1C1N1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv), P1C1N1UV1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex), P1C1N1UV1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw), P1C1N1UV1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), P1C1N1UV1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw), P1C1N1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex), P1C1N1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::tex), P1C1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::uv), P1C1UV1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::tex), P1C1UV1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw), P1C1UV1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), P1C1UV1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::uvw), P1C1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::color) | (1 << Index::uvw) | (1 << Index::tex), P1C1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal), P1N1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::tex), P1N1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv), P1N1UV1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::tex), P1N1UV1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw), P1N1UV1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), P1N1UV1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::uvw), P1N1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::normal) | (1 << Index::uvw) | (1 << Index::tex), P1N1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::tex), P1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::uv), P1UV1::VertexArray },
		{ (1 << Index::position) | (1 << Index::uv) | (1 << Index::tex), P1UV1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::uv) | (1 << Index::uvw), P1UV1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), P1UV1UVW1T1::VertexArray },
		{ (1 << Index::position) | (1 << Index::uvw), P1UVW1::VertexArray },
		{ (1 << Index::position) | (1 << Index::uvw) | (1 << Index::tex), P1UVW1T1::VertexArray },
		{ (1 << Index::tex), T1::VertexArray },
		{ (1 << Index::uv), UV1::VertexArray },
		{ (1 << Index::uv) | (1 << Index::tex), UV1T1::VertexArray },
		{ (1 << Index::uv) | (1 << Index::uvw), UV1UVW1::VertexArray },
		{ (1 << Index::uv) | (1 << Index::uvw) | (1 << Index::tex), UV1UVW1T1::VertexArray },
		{ (1 << Index::uvw), UVW1::VertexArray },
		{ (1 << Index::uvw) | (1 << Index::tex), UVW1T1::VertexArray },
	};
}