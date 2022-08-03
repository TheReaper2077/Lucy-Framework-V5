#pragma once

namespace lgl {
	bool IsInitialized();
	void Initialize(void* loadprocaddress);

	void Viewport(int x, int y, int width, int height);
}