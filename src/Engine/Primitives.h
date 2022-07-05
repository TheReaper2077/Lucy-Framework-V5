#pragma once

#include "Vertex.h"

namespace lucy::Primitives {
	lgl::IndexBuffer* GetWireQuadIndices(int vertexcount);
	lgl::IndexBuffer* GetQuadIndices(int vertexcount);

	void QuadIndexed(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size);
	void QuadIndexed(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	void QuadIndexed(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1);
	void QuadIndexed(std::vector<Vertex::P1C1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1);
	void QuadIndexed(std::vector<Vertex::P1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int idx);
	void QuadIndexed(std::vector<Vertex::P1C1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int idx);
	void QuadIndexed(std::vector<Vertex::P1UV1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx);
	void QuadIndexed(std::vector<Vertex::P1C1UV1I1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx);
	void QuadIndexed(std::vector<Vertex::P1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1C1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int idx, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1C1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int idx, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1UV1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1C1UV1I1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int idx, const unsigned int tex);
}
