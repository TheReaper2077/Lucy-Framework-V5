#pragma once

namespace lgl {
	enum Type {
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		FLOAT,
		FIXED,

		UNSIGNED_INT_24_8,
	};

	const unsigned int Map(const Type type);

	enum Format {
		RGB,
		RGBA,

		RGBA32F,
		RGB32F,
		RGBA16F,
		RGB16F,
		
		DEPTH_STENCIL,
		DEPTH24_STENCIL8,
	};

	const unsigned int Map(const Format format);

	enum Primitive {
		POINT,
		LINE,
		TRIANGLE,
		LINE_STRIP,
		TRIANGLE_FAN,
		TRIANGLE_STRIP,
	};

	const unsigned int Map(const Primitive primitive);

	enum TextureFilteringMode {
		FilterMode_None = 0,
		FilterMode_LINEAR,
		FilterMode_NEAREST,
	};

	const unsigned int Map(const TextureFilteringMode texturefilteringmode);

	enum TextureWrapMode {
		WrapMode_None = 0,
		WrapMode_CLAMP_TO_EDGE,
		WrapMode_CLAMP_TO_BORDER,
		WrapMode_MIRRORED_REPEAT,
		WrapMode_REPEAT,
		WrapMode_MIRROR_CLAMP_TO_EDGE,
	};

	const unsigned int Map(const TextureWrapMode texturewrapmode);

	enum TextureMode {
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_1D_ARRAY,
		TEXTURE_2D_ARRAY,
		TEXTURE_RECTANGLE,
		TEXTURE_CUBE_MAP,
		TEXTURE_CUBE_MAP_ARRAY,
		TEXTURE_BUFFER,
		TEXTURE_2D_MULTISAMPLE,
		TEXTURE_2D_MULTISAMPLE_ARRAY,
	};

	const unsigned int Map(const TextureMode texturemode);

	enum Attachment {
		COLOR_ATTACHMENT0,
		COLOR_ATTACHMENT1,
		COLOR_ATTACHMENT2,
		COLOR_ATTACHMENT3,
		COLOR_ATTACHMENT4,
		COLOR_ATTACHMENT5,
		COLOR_ATTACHMENT6,
		COLOR_ATTACHMENT7,
		COLOR_ATTACHMENT8,
		COLOR_ATTACHMENT9,
		COLOR_ATTACHMENT10,
		COLOR_ATTACHMENT11,
		COLOR_ATTACHMENT12,
		COLOR_ATTACHMENT13,
		COLOR_ATTACHMENT14,
		COLOR_ATTACHMENT15,
		COLOR_ATTACHMENT16,
		COLOR_ATTACHMENT17,
		COLOR_ATTACHMENT18,
		COLOR_ATTACHMENT19,
		COLOR_ATTACHMENT20,
		COLOR_ATTACHMENT21,
		COLOR_ATTACHMENT22,
		COLOR_ATTACHMENT23,
		COLOR_ATTACHMENT24,
		COLOR_ATTACHMENT25,
		COLOR_ATTACHMENT26,
		COLOR_ATTACHMENT27,
		COLOR_ATTACHMENT28,
		COLOR_ATTACHMENT29,
		COLOR_ATTACHMENT30,
		COLOR_ATTACHMENT31,
		DEPTH_ATTACHMENT,
		STENCIL_ATTACHMENT,
		DEPTH_STENCIL_ATTACHMENT,
	};

	const unsigned int Map(const Attachment atachment);

	using BitFlags = unsigned int;

	extern const BitFlags COLOR_BUFFER_BIT;
	extern const BitFlags DEPTH_BUFFER_BIT;
	extern const BitFlags STENCIL_BUFFER_BIT;
}