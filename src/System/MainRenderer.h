#pragma once

#include <Engine/ECS.h>
#include <LucyGL/LucyGL.h>
#include <LucyRE/LucyRE.h>
#include <set>
#include <vector>
#include <unordered_map>
#include <Structures/Structures.h>

namespace lucy {
	struct MainRenderer {
	private:
		using WireVertex = lre::Vertex::P1;

		using TexVertex = lre::Vertex::P1UV1T1;
		using ColorVertex = lre::Vertex::P1C1;
		using TexColorVertex = lre::Vertex::P1C1UV1T1;

		lre::TextureStore sprite_texture_store;

		std::set<lucy::Entity> lighting_entities;
		std::unordered_map<lucy::Material*, std::vector<lucy::Entity>> mesh_material_entities, sprite_material_entities;

		int directional_light_count = 0;
		int point_light_count = 0;
		int spot_light_count = 0;
		int areal_light_count = 0;

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
		void FlushSprite();
		
		template <typename T>
		void FlushDebugLines();

		// Shader
		lgl::Shader* sprite_shader = nullptr;
		lgl::Shader* sprite_circle_shader = nullptr;
		lgl::Shader* pbr_mesh_shader = nullptr;
		lgl::Shader* mesh_shader = nullptr;
		lgl::Shader* pbr_sphere_shader = nullptr;
		lgl::Shader* pbr_sprite_shader = nullptr;
		lgl::Shader* line_shader = nullptr;
		lgl::Shader* screen_shader = nullptr;

		bool shader_init = false;

		void SetMaterial(lgl::Shader* shader, Material* material);
		void RenderFramebuffer(lgl::FrameBuffer* framebuffer);

	public:
		void SetLightAndShaders(Registry& registry);
		void UpdateLigtingShaders(Registry& registry);

		// Main Systems
		void DebugRender(Registry& registry);
		void MeshRender(Registry& registry);
		void SpriteRender(Registry& registry);

		void Render(Registry& registry);
	};
}