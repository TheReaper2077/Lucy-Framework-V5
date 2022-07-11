#pragma once

#include "API.h"

namespace lgl {
	template <typename ...Args>
	Texture* MakeTexture(Args ...params);

	template <typename ...Args>
	Shader* MakeShader(Args ...params);

	template <typename ...Args>
	FrameBuffer* MakeFrameBuffer(Args ...params);

	template <typename ...Args>
	UniformBuffer* MakeUniformBuffer(Args ...params);

	template <typename ...Args>
	VertexArray* MakeVertexArray(Args ...params);

	template <typename ...Args>
	VertexBuffer* MakeVertexBuffer(Args ...params);

	template <typename ...Args>
	IndexBuffer* MakeIndexBuffer(Args ...params);
}