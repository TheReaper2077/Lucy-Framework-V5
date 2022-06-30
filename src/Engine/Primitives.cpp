#include "Primitives.h"

void lucy::Primitives::Quad(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size) {
	vertices.reserve(6 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1 {{ position.x - size.x, position.y - size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x - size.x, position.y + size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x + size.x, position.y + size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x + size.x, position.y + size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x + size.x, position.y - size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x - size.x, position.y - size.y, 0 }});
}

void lucy::Primitives::Quad(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
	vertices.reserve(6 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x - size.x, position.y - size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x - size.x, position.y + size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x + size.x, position.y + size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x + size.x, position.y + size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x + size.x, position.y - size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x - size.x, position.y - size.y, 0 }, color });
}

void lucy::Primitives::Quad(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int id) {
	vertices.reserve(6 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y + size.y, 0 }, { uv0.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y - size.y, 0 }, { uv1.x, uv0.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }, (float)id });
}

void lucy::Primitives::Quad(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1) {
	vertices.reserve(6 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }});
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x - size.x, position.y + size.y, 0 }, { uv0.x, uv1.y }});
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }});
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }});
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x + size.x, position.y - size.y, 0 }, { uv1.x, uv0.y }});
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }});
}

void lucy::Primitives::Quad(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const glm::vec4& color, const unsigned int id) {
	vertices.reserve(6 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, color, { uv0.x, uv0.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x - size.x, position.y + size.y, 0 }, color, { uv0.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, color, { uv1.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, color, { uv1.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x + size.x, position.y - size.y, 0 }, color, { uv1.x, uv0.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1C1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, color, { uv0.x, uv0.y }, (float)id });
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int id) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y + size.y, 0 }, { uv0.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y - size.y, 0 }, { uv1.x, uv0.y }, (float)id });
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1UV1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }});
	vertices.emplace_back(lucy::Vertex::P1UV1 {{ position.x - size.x, position.y + size.y, 0 }, { uv0.x, uv1.y }});
	vertices.emplace_back(lucy::Vertex::P1UV1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }});
	vertices.emplace_back(lucy::Vertex::P1UV1 {{ position.x + size.x, position.y - size.y, 0 }, { uv1.x, uv0.y }});
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const glm::vec4& color, const unsigned int id) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y - size.y, 0 }, { uv0.x, uv0.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x - size.x, position.y + size.y, 0 }, { uv0.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y + size.y, 0 }, { uv1.x, uv1.y }, (float)id });
	vertices.emplace_back(lucy::Vertex::P1UV1T1 {{ position.x + size.x, position.y - size.y, 0 }, { uv1.x, uv0.y }, (float)id });
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x - size.x, position.y - size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x - size.x, position.y + size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x + size.x, position.y + size.y, 0 }, color });
	vertices.emplace_back(lucy::Vertex::P1C1 {{ position.x + size.x, position.y - size.y, 0 }, color });
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(lucy::Vertex::P1 {{ position.x - size.x, position.y - size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x - size.x, position.y + size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x + size.x, position.y + size.y, 0 }});
	vertices.emplace_back(lucy::Vertex::P1 {{ position.x + size.x, position.y - size.y, 0 }});
}

lgl::IndexBuffer* lucy::Primitives::GetWireQuadIndices(int vertexcount) {
	static lgl::IndexBuffer indexbuffer;
	static int indexcount;

	if (vertexcount % 2 != 0) vertexcount++;

	if (vertexcount*2 > indexcount) {
		std::vector<uint32_t> indices;

		indices.reserve(vertexcount*2);

		for (int i = 0; i < vertexcount; i++) {
			indices.emplace_back(0 + i*4);
			indices.emplace_back(1 + i*4);
			indices.emplace_back(1 + i*4);
			indices.emplace_back(2 + i*4);
			indices.emplace_back(2 + i*4);
			indices.emplace_back(3 + i*4);
			indices.emplace_back(3 + i*4);
			indices.emplace_back(0 + i*4);
		}

		indexbuffer.Bind();
		indexbuffer.AddData(indices.data(), indices.size()*sizeof(uint32_t));

		indices.clear();
		indexcount = vertexcount*2;
	}

	return &indexbuffer;
}

lgl::IndexBuffer* lucy::Primitives::GetQuadIndices(int vertexcount) {
	static lgl::IndexBuffer indexbuffer;
	static int indexcount;

	if (vertexcount*1.5 > indexcount) {
		std::vector<uint32_t> indices;

		indices.reserve(vertexcount*1.5);

		for (int i = 0; i < vertexcount; i++) {
			indices.emplace_back(0 + i*4);
			indices.emplace_back(1 + i*4);
			indices.emplace_back(2 + i*4);
			indices.emplace_back(2 + i*4);
			indices.emplace_back(3 + i*4);
			indices.emplace_back(0 + i*4);
		}

		indexbuffer.Bind();
		indexbuffer.AddData(indices.data(), indices.size()*sizeof(uint32_t));

		indices.clear();
		indexcount = vertexcount*1.5;
	}

	return &indexbuffer;
}
