#pragma once

#include <LucyGL/LucyGL.h>
#include <unordered_map>
#include <array>
#include <assert.h>
#include <memory>

namespace lucy {
	enum MeshVAOAttrib_ {
		MeshVAOAttrib_POSITION = 0,
		MeshVAOAttrib_COLOR = 1,
		MeshVAOAttrib_NORMAL = 2,
		MeshVAOAttrib_UV,
		MeshVAOAttrib_UVW,

		MeshVAOAttrib_COUNT
	};

	enum MeshVAOAttribFlag_ {
		MeshVAOAttribFlag_POSITION = 1 << MeshVAOAttrib_POSITION,
		MeshVAOAttribFlag_NORMAL = 1 << MeshVAOAttrib_NORMAL,
		MeshVAOAttribFlag_COLOR = 1 << MeshVAOAttrib_COLOR,
		MeshVAOAttribFlag_UV = 1 << MeshVAOAttrib_UV,
		MeshVAOAttribFlag_UVW = 1 << MeshVAOAttrib_UVW,
	};

	struct MeshVAORegistry {
	private:
		std::unordered_map<MeshVAOAttrib_, MeshVAOAttribFlag_> MeshVAOAttribFlagMap_ = {
			{ MeshVAOAttrib_POSITION, MeshVAOAttribFlag_POSITION },
			{ MeshVAOAttrib_NORMAL, MeshVAOAttribFlag_NORMAL },
			{ MeshVAOAttrib_COLOR, MeshVAOAttribFlag_COLOR },
			{ MeshVAOAttrib_UV, MeshVAOAttribFlag_UV },
			{ MeshVAOAttrib_UVW, MeshVAOAttribFlag_UVW },
		};

		std::unordered_map<MeshVAOAttrib_, uint32_t> MeshVAOAttribSizeMap_= {
			{ MeshVAOAttrib_POSITION, 3 },
			{ MeshVAOAttrib_NORMAL, 3 },
			{ MeshVAOAttrib_COLOR, 4 },
			{ MeshVAOAttrib_UV, 2 },
			{ MeshVAOAttrib_UVW, 3 },
		};
		
	public:
		std::unordered_map<size_t, std::shared_ptr<lgl::VertexArray>> bit_layout;
		std::unordered_map<size_t, std::shared_ptr<lgl::VertexArray>> custom_layout;

		std::unordered_map<lgl::VertexArray*, std::array<uint32_t, MeshVAOAttrib_COUNT>> offset;
		std::unordered_map<lgl::VertexArray*, std::array<bool, MeshVAOAttrib_COUNT>> is_present;

		MeshVAORegistry() {}
		~MeshVAORegistry() {}

		template <typename T>
		lgl::VertexArray* SetVertexArray(std::vector<lgl::VertexArrayAttribDescriptor> descriptor) {
			if (custom_layout.find(typeid(T).hash_code()) == custom_layout.end())
				custom_layout[typeid(T).hash_code()] = std::make_shared<lgl::VertexArray>(descriptor);

			return custom_layout[typeid(T).hash_code()].get();
		}

		template <typename T>
		lgl::VertexArray* GetVertexArray() {
			assert(custom_layout.find(typeid(T).hash_code()) != custom_layout.end());

			return custom_layout[typeid(T).hash_code()].get();
		}

		lgl::VertexArray* GetVertexArray(uint32_t flags);
		
		size_t GetOffset(lgl::VertexArray* vertexarray, MeshVAOAttrib_ attrib) {
			assert(attrib < MeshVAOAttrib_COUNT);

			return offset[vertexarray][attrib];
		}
		std::array<uint32_t, MeshVAOAttrib_COUNT>& GetOffset(lgl::VertexArray* vertexarray) {
			return offset[vertexarray];
		}
		std::array<bool, MeshVAOAttrib_COUNT>& GetPresent(lgl::VertexArray* vertexarray) {
			return is_present[vertexarray];
		}
		bool IsAttribPresent(lgl::VertexArray* vertexarray, MeshVAOAttrib_ attrib) {
			assert(attrib < MeshVAOAttrib_COUNT);
			
			return is_present[vertexarray][attrib];
		}
	};
}