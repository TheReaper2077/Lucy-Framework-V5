#include "Camera.h"
#include "Transform.h"
#include <Lucy/Lucy.h>
#include <glm/gtc/matrix_transform.hpp>

static auto& registry = lucy::Registry::Instance();

lucy::Camera::Camera() {
	// world_up = { 0.0, -1.0, 0.0 };
}

lucy::Camera::~Camera() {
	if (framebuffer != nullptr)
		delete framebuffer;
	framebuffer = nullptr;
}
