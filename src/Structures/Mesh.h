#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>
#include <array>
#include <vector>
#include <LucyRE/LucyRE.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lucy {
	struct Mesh {
		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;
		lgl::VertexArray* vertexarray = nullptr;

		int vertexcount = 0;
		int indexcount = 0;

		lgl::Primitive primitive = lgl::TRIANGLE;

		Mesh() {}
		~Mesh() {}
	};
}