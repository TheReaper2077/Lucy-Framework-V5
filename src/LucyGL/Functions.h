#pragma once

namespace lgl {
	bool IsInitialized();
	void Initialize(void* loadprocaddress);

	void Viewport(int x, int y, int width, int height);

	void Clear(float r, float g, float b, float a, unsigned int flags);
	void Clear(unsigned int flags);
	void ClearColor(float r, float g, float b, float a);
}