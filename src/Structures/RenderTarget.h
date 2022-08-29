#pragma once

#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>
#include <Lucy/UUID.h>
#include <unordered_map>

namespace lucy {
	struct RenderTarget {
		lgl::FrameBuffer* framebuffer = nullptr;
		std::unordered_map<lgl::Attachment, lgl::Texture*> texture_store;

		RenderTarget() {}
		~RenderTarget();

		void Initialize();
		void AddColorAttachment(int index);
		void SetAttachmentTexture(lgl::Attachment attachment, lgl::Texture* texture);
		lgl::Texture* GetAttachmentTexture(lgl::Attachment attachment);

		bool HasDepthBuffer();
		bool HasStencilBuffer();
		bool HasColorBuffer(int index);
		bool HasColorBuffer();
		bool HasBuffer(lgl::Attachment attachment);

		void ReadPixel(lgl::Attachment attachment, const glm::vec2& pos, float* pixel);
	};
}