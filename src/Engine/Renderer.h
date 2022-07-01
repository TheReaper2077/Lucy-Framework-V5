#pragma once

#include <LucyGL/API.h>
#include <glm/glm.hpp>

#include "Primitives.h"
#include "ShaderRegistry.h"

namespace lucy {
	class Renderer {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		lgl::UniformBuffer* uniformbuffer = nullptr;

	public:
		ShaderRegistry shaderregistry;

		void SetModel(const glm::mat4& model);
		void SetView(const glm::mat4& view);
		void SetProjection(const glm::mat4& projection);

		void SetPerspective();
		void SetOrtho(const float left, const float right, const float top, const float bottom, const float near, const float far);

		Renderer();
		~Renderer();
	};
}