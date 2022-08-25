#pragma once

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

		static void SetModel(const glm::mat4& model);
		static void SetView(const glm::mat4& view);
		static void SetProjection(const glm::mat4& projection);
		static void SetViewPosition(const glm::vec3& view_position);

		static void Initialize();

		static void SetFrameBuffer(lgl::FrameBuffer* framebuffer);
		static void SetShader(lgl::Shader* shader);
		static void SetVertexArray(lgl::VertexArray* vertexarray);
		static void SetVertexBuffer(lgl::VertexBuffer* vertexbuffer);
		static void SetIndexBuffer(lgl::IndexBuffer* indexbuffer);

	private:
		#define self Instance()

		static Renderer* Instance() {
			static Renderer instance;
			return &instance;
		}
	};
}
