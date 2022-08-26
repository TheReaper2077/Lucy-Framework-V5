#pragma once

#include <string>
#include <memory>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lre {
	struct Renderer {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_position;

		std::unique_ptr<lgl::UniformBuffer> uniformbuffer;

		lgl::FrameBuffer* framebuffer = nullptr;
		lgl::Shader* shader = nullptr;
		lgl::VertexArray* vertexarray = nullptr;
		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;

		int dir_light = 0;
		int point_light = 0;

		std::unordered_map<std::string, lgl::Shader> shader_registry;

		static Renderer* Instance() {
			static Renderer instance;
			return &instance;
		}
	};

	void SetModel(const glm::mat4& model);
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);
	void SetViewPosition(const glm::vec3& view_position);

	void Initialize();
	void InitializeMainShaders();

	void PrepareShadersForRendering();

	void SetFrameBuffer(lgl::FrameBuffer* framebuffer);
	void SetShader(lgl::Shader* shader);
	void SetVertexArray(lgl::VertexArray* vertexarray);
	void SetVertexBuffer(lgl::VertexBuffer* vertexbuffer);
	void SetIndexBuffer(lgl::IndexBuffer* indexbuffer);

	void InsertShader(std::string name, lgl::Shader shader);
	lgl::Shader* GetShader(std::string name);

	void RederFrameBufferToScreen(lgl::FrameBuffer* framebuffer);
}
