#pragma once

#include "RenderPass.h"
#include "Renderer.h"
#include "TextureStore.h"
#include <Components/Components.h>
#include "ECS.h"

namespace lucy {
	class SpriteRenderPass: public RenderPass {
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

	public:
		SpriteRenderPass() {}

		void FirstInit() override;
		void Init() override;
		void Render(lgl::FrameBuffer* framebuffer) override;
		void Render(Camera& camera);
		void Render();
	};
}