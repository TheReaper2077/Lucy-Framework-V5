#include <LucyGL/Functions.h>
#include <LucyGL/Types.h>
#include <glad/glad.h>
#include <assert.h>

static bool init = false;

void lgl::Initialize(void* loadprocaddress) {
	assert(!init);

	gladLoadGLLoader((GLADloadproc)loadprocaddress);

	CheckValues();

	init = true;
}

bool lgl::IsInitialized() {
	return init;
}

void lgl::Viewport(int x, int y, int width, int height) {
	glViewport(x, y, width, height);
}