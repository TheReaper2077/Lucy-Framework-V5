#pragma once

#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

#include "Primitives.h"
#include "TextureStore.h"
#include <vector>
#include <memory>
#include "RenderPass.h"

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

		std::unordered_map<uint32_t, std::shared_ptr<RenderPass>> renderpass_map;

		template <typename T>
		std::vector<T>& GetVertices() {
			static std::vector<T> vector;
			return vector;
		}
		
		template <typename T>
		lgl::VertexBuffer* AddData(std::vector<T>& vertices) {
			static lgl::VertexBuffer vertexbuffer;

			vertexbuffer.Bind();
			vertexbuffer.Allocate(sizeof(T)*vertices.size());
			vertexbuffer.AddDataDynamic(vertices.data(), sizeof(T)*vertices.size());
			return &vertexbuffer;
		}

		template <typename T>
		lgl::VertexBuffer* AddData() {
			return AddData(GetVertices<T>());
		}
		
		template <typename T>
		void Flush();
		void Flush();

		TextureStore texture_store;
		lgl::Shader* shader = nullptr;

		std::set<Entity> lighting_entities;
		std::unordered_map<Material*, std::vector<Entity>> material_entities;

	public:
		void Init();

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

		void RenderMain();

		template <typename T>
		void AddRenderPass() {
			if (renderpass_map.find(typeid(T).hash_code()) == renderpass_map.end()) {
				renderpass_map[typeid(T).hash_code()] = std::static_pointer_cast<RenderPass>(std::make_shared<T>());
				renderpass_map[typeid(T).hash_code()]->FirstInit();
			}
		}

		void SetShader(const std::string& name, const std::string& vs_filename, const std::string& fs_filename);
		lgl::Shader* GetPBRShader(const std::string& name);
		lgl::Shader* GetShader(const std::string& name);

		Renderer();
		~Renderer();
	};
}
