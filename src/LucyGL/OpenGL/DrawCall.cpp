#include <LucyGL/Status.h>
#include <LucyGL/DrawCall.h>

#include <glad/glad.h>
#include <assert.h>

enum DrawMode {
	NONE,
	INDIRECT,
	INSTANCED,
	INSTANCED_BASEINSTANCE,
	
	INDEXED,
	INDEXED_INDIRECT,
	INDEXED_INSTANCED,
	INDEXED_BASEVERTEX,
	INDEXED_INSTANCED_BASEINSTANCE,
	INDEXED_INSTANCED_BASEVERTEX,
	INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE,

	MULTI,
	MULTI_INDIRECT,
	MULTI_INDIRECTCOUNT,

	INDEXED_MULTI,
	INDEXED_MULTI_BASEVERTEX,
	INDEXED_MULTI_INDIRECT,
	INDEXED_MULTI_INDIRECTCOUNT,

	RANGE_INDEXED,
	RANGE_INDEXED_BASEVERTEX,

	PIXELS,

	COUNT
};

bool DrawCmd(DrawMode drawmode, lgl::Primitive mode, lgl::Type type, lgl::Format format, int first, int start, int end, int count, int basevertex, int baseinstance, int instancecount, int width, int height, void* indices, void* indirect, void* pixels) {
	switch (drawmode) {
		case NONE:
			glDrawArrays(lgl::Map(mode), first, count);
			break;
		case INDIRECT:
			glDrawArraysIndirect(lgl::Map(mode), indirect);
			break;
		case INSTANCED:
			glDrawArraysInstanced(lgl::Map(mode), first, count, instancecount);
			break;
		case INSTANCED_BASEINSTANCE:
			glDrawArraysInstancedBaseInstance(lgl::Map(mode), first, count, instancecount, baseinstance);
			break;
			
		case INDEXED:
			glDrawElements(lgl::Map(mode), count, lgl::Map(type), indices);
			break;
		case INDEXED_INDIRECT:
			glDrawElementsIndirect(lgl::Map(mode), lgl::Map(type), indirect);
			break;
		case INDEXED_INSTANCED:
			glDrawElementsInstanced(lgl::Map(mode), count, lgl::Map(type), indices, instancecount);
			break;
		case INDEXED_BASEVERTEX:
			glDrawElementsBaseVertex(lgl::Map(mode), count, lgl::Map(type), indices, basevertex);
			break;
		case INDEXED_INSTANCED_BASEINSTANCE:
			glDrawElementsInstancedBaseVertex(lgl::Map(mode), count, lgl::Map(type), indices, instancecount, basevertex);
			break;
		case INDEXED_INSTANCED_BASEVERTEX:
			glDrawElementsInstancedBaseVertex(lgl::Map(mode), count,  lgl::Map(type), indices, instancecount, basevertex);
			break;
		case INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE:
			glDrawElementsInstancedBaseVertexBaseInstance(lgl::Map(mode), count, lgl::Map(type), indices, instancecount, basevertex, baseinstance);
			break;
		
		case MULTI:
			break;
		case MULTI_INDIRECT:
			break;
		case MULTI_INDIRECTCOUNT:
			break;

		case INDEXED_MULTI:
			break;
		case INDEXED_MULTI_BASEVERTEX:
			break;
		case INDEXED_MULTI_INDIRECT:
			break;
		case INDEXED_MULTI_INDIRECTCOUNT:
			break;
		
		case RANGE_INDEXED:
			glDrawRangeElements(lgl::Map(mode), start, end, count, lgl::Map(type), indices);
			break;
		case RANGE_INDEXED_BASEVERTEX:
			glDrawRangeElementsBaseVertex(lgl::Map(mode), start, end, count, lgl::Map(type), indices, basevertex);
			break;

		case PIXELS:
			glDrawPixels(width, height, lgl::Map(format), lgl::Map(type), pixels);
			break;

		default:
			return false;
	}

	// lgl::GetStatus().drawcount++;

	return true;
}

bool lgl::DrawIndexed(Primitive mode, int count, Type type, void* indices) {
	return DrawCmd(INDEXED, mode, type, (Format)0, 0, 0, 0, count, 0, 0, 0, 0, 0, indices, nullptr, nullptr);
}

bool lgl::MultiDrawIndexed(Primitive mode, int count, Type type, void* indices) {
	assert(false);
}

bool lgl::Draw(Primitive mode, int first, int count) {
	return DrawCmd(NONE, mode, (Type)0, (Format)0, first, 0, 0, count, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr);
}