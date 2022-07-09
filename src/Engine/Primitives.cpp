#include "Primitives.h"
#include <glm/gtc/quaternion.hpp>

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


void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position});
	vertices.emplace_back(Vertex::P1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position});
	vertices.emplace_back(Vertex::P1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position});
	vertices.emplace_back(Vertex::P1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color});
	vertices.emplace_back(Vertex::P1C1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color});
	vertices.emplace_back(Vertex::P1C1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color});
	vertices.emplace_back(Vertex::P1C1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }});
	vertices.emplace_back(Vertex::P1UV1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }});
	vertices.emplace_back(Vertex::P1UV1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }});
	vertices.emplace_back(Vertex::P1UV1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }});
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }});
	vertices.emplace_back(Vertex::P1C1UV1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }});
	vertices.emplace_back(Vertex::P1C1UV1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }});
	vertices.emplace_back(Vertex::P1C1UV1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int idx) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1I1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, (float)idx});
	vertices.emplace_back(Vertex::P1I1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, (float)idx});
	vertices.emplace_back(Vertex::P1I1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, (float)idx});
	vertices.emplace_back(Vertex::P1I1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int idx) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1I1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, (float)idx});
	vertices.emplace_back(Vertex::P1C1I1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, (float)idx});
	vertices.emplace_back(Vertex::P1C1I1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, (float)idx});
	vertices.emplace_back(Vertex::P1C1I1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1I1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }, (float)idx});
	vertices.emplace_back(Vertex::P1UV1I1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1UV1I1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1UV1I1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1I1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }, (float)idx});
	vertices.emplace_back(Vertex::P1C1UV1I1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1C1UV1I1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1C1UV1I1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, (float)tex});
	vertices.emplace_back(Vertex::P1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, (float)tex});
	vertices.emplace_back(Vertex::P1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, (float)tex});
	vertices.emplace_back(Vertex::P1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, (float)tex});
	vertices.emplace_back(Vertex::P1C1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, (float)tex});
	vertices.emplace_back(Vertex::P1C1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, (float)tex});
	vertices.emplace_back(Vertex::P1C1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }, (float)tex});
	vertices.emplace_back(Vertex::P1UV1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1UV1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1UV1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int idx, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1I1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1I1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1I1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1I1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, (float)idx, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int idx, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1I1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1I1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1I1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1I1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, (float)idx, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1I1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1UV1I1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1UV1I1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1UV1I1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }, (float)idx, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const unsigned int tex) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1I1T1 { glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1I1T1 { glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1I1T1 { glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1I1T1 { glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }, (float)idx, (float)tex});
}


void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position });
	vertices.emplace_back(Vertex::P1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position });
	vertices.emplace_back(Vertex::P1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position });
	vertices.emplace_back(Vertex::P1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position });
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color});
	vertices.emplace_back(Vertex::P1C1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color});
	vertices.emplace_back(Vertex::P1C1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color});
	vertices.emplace_back(Vertex::P1C1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }});
	vertices.emplace_back(Vertex::P1UV1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }});
	vertices.emplace_back(Vertex::P1UV1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }});
	vertices.emplace_back(Vertex::P1UV1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }});
}

void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }});
	vertices.emplace_back(Vertex::P1C1UV1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }});
	vertices.emplace_back(Vertex::P1C1UV1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }});
	vertices.emplace_back(Vertex::P1C1UV1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int idx, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1I1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, (float)idx});
	vertices.emplace_back(Vertex::P1I1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, (float)idx});
	vertices.emplace_back(Vertex::P1I1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, (float)idx});
	vertices.emplace_back(Vertex::P1I1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int idx, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1I1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, (float)idx});
	vertices.emplace_back(Vertex::P1C1I1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, (float)idx});
	vertices.emplace_back(Vertex::P1C1I1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, (float)idx});
	vertices.emplace_back(Vertex::P1C1I1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1I1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }, (float)idx});
	vertices.emplace_back(Vertex::P1UV1I1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1UV1I1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1UV1I1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1I1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }, (float)idx});
	vertices.emplace_back(Vertex::P1C1UV1I1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1C1UV1I1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }, (float)idx});
	vertices.emplace_back(Vertex::P1C1UV1I1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }, (float)idx});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, (float)tex});
	vertices.emplace_back(Vertex::P1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, (float)tex});
	vertices.emplace_back(Vertex::P1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, (float)tex});
	vertices.emplace_back(Vertex::P1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, (float)tex});
	vertices.emplace_back(Vertex::P1C1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, (float)tex});
	vertices.emplace_back(Vertex::P1C1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, (float)tex});
	vertices.emplace_back(Vertex::P1C1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }, (float)tex});
	vertices.emplace_back(Vertex::P1UV1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1UV1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1UV1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int idx, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1I1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1I1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1I1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1I1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, (float)idx, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int idx, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1I1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1I1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1I1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1I1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, (float)idx, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1UV1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1UV1I1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, { uv0.x, uv0.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1UV1I1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, { uv0.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1UV1I1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, { uv1.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1UV1I1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, { uv1.x, uv0.y }, (float)idx, (float)tex});
}
void lucy::Primitives::QuadIndexed(std::vector<Vertex::P1C1UV1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const unsigned int tex, const glm::quat& quaternion) {
	vertices.reserve(4 + vertices.size());

	vertices.emplace_back(Vertex::P1C1UV1I1T1 { quaternion * glm::vec3(-size.x / 2, -size.y / 2, 0) + position, color, { uv0.x, uv0.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1I1T1 { quaternion * glm::vec3(-size.x / 2, +size.y / 2, 0) + position, color, { uv0.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1I1T1 { quaternion * glm::vec3(+size.x / 2, +size.y / 2, 0) + position, color, { uv1.x, uv1.y }, (float)idx, (float)tex});
	vertices.emplace_back(Vertex::P1C1UV1I1T1 { quaternion * glm::vec3(+size.x / 2, -size.y / 2, 0) + position, color, { uv1.x, uv0.y }, (float)idx, (float)tex});
}