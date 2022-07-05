#pragma once

#include <LucyGL/API.h>
#include <glm/glm.hpp>

#include "Primitives.h"
#include "ShaderRegistry.h"
#include "TextureStore.h"

namespace lucy {
	class Renderer {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		lgl::UniformBuffer* uniformbuffer = nullptr;

	public:
		ShaderRegistry shaderregistry;

		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);

		void SetPerspective();
		void SetOrtho(const float left, const float right, const float top, const float bottom, const float near, const float far);

		void RenderQuads(lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount);
		void RenderQuads(lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, TextureStore& texture_store);
		void RenderTextureIdQuads(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, TextureStore& texture_store);
		void RenderTextureIdQuads(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount);
		void RenderUniformTextureIdQuads(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, int textureid);
		void RenderUniformColor(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount, const glm::vec4& color);
		void RenderColor(lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, size_t vertexcount);

		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count);
		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count);
		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures);
		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures);

		Renderer();
		~Renderer();
	};
}
