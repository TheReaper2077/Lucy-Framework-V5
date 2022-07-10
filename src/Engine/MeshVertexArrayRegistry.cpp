#include "MeshVertexArrayRegistry.h"
#include <iostream>
#include <bitset>

lgl::VertexArray* lucy::MeshVAORegistry::GetVertexArray(uint32_t flags) {
	if (bit_layout.find(flags) == bit_layout.end()) {
		std::vector<lgl::VertexArrayAttribDescriptor> descriptor;
		std::array<bool, MeshVAOAttrib_COUNT> attrib_present;
		std::array<uint32_t, MeshVAOAttrib_COUNT> attrib_offset;

		uint32_t offset = 0;

		for (uint32_t i = 0; i < MeshVAOAttrib_COUNT; i++) {
			if ((flags >> i) & 1) {
				attrib_offset[i] = offset;
				attrib_present[i] = true;

				descriptor.push_back({ i, (unsigned int)MeshVAOAttribSizeMap_[(MeshVAOAttrib_)i], lgl::FLOAT });
				offset += MeshVAOAttribSizeMap_[(MeshVAOAttrib_)i];
			} else {
				attrib_present[i] = false;
			}
		}

		auto vertexarray = std::make_shared<lgl::VertexArray>(descriptor);
		bit_layout[flags] = vertexarray;
		this->offset[vertexarray.get()] = attrib_offset;
		this->is_present[vertexarray.get()] = attrib_present;
	}

	return bit_layout[flags].get();
}
