#pragma once

#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>
#include "Primitives.h"
#include "TextureStore.h"
#include <vector>
#include <memory>

namespace lre {
	static enum ShaderStates {
		TEXTURE,
		TEXTURE_COLOR,
		TEXTURE_UCOLOR,
		UTEXTURE,
		UTEXTURE_COLOR,
		UTEXTURE_UCOLOR,
		COLOR,
		UCOLOR = 7,
	};

	struct RenderContext {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_pos;

		lgl::UniformBuffer* uniformbuffer = nullptr;
		std::unordered_map<std::string, lgl::Shader*> shader_map;

		RenderContext() {}
		~RenderContext() {}
	};

	void Initialize();

	void SetModel(const glm::mat4& model);
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);
	void SetViewPos(const glm::vec3& projection);

	void SetPerspective(float fovy, float aspect, float vnear, float vfar);
	void SetOrtho(const float left, const float right, const float top, const float bottom, const float vnear, const float vfar);

	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count);
	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count);
	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures);
	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures);

	void RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int count);
	void RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int count, TextureStore& textures);

	void Clear();
	void Clear(const glm::vec4& color);
	void Clear(const glm::vec3& color);
}
