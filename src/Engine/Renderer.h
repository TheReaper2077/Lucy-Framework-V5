#pragma once

#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

#include "Primitives.h"
#include "TextureStore.h"

namespace lucy {
	class Renderer {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_pos;

		lgl::UniformBuffer* uniformbuffer = nullptr;
		std::unordered_map<std::string, lgl::Shader*> shader_map;

		typedef std::string vertex_src;
		typedef std::string fragment_src;

		std::unordered_map<std::string, std::pair<vertex_src, fragment_src>> shader_src_map;

	public:
		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);
		void SetViewPos(const glm::vec3& projection);

		void SetPerspective();
		void SetOrtho(const float left, const float right, const float top, const float bottom, const float near, const float far);

		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count);
		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count);
		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures);
		void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures);

		void RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int count);
		void RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int count, TextureStore& textures);

		void Clear();
		void Clear(const glm::vec4& color);
		void Clear(const glm::vec3& color);

		void SetShader(const std::string& name, const std::string& vs_filename, const std::string& fs_filename);
		lgl::Shader* GetPBRShader(const std::string& name);
		lgl::Shader* GetShader(const std::string& name);

		Renderer();
		~Renderer();
	};
}
