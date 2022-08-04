#pragma once

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

namespace ImGui {
	void SanitisedInputText(const char* label, std::string& text);

	void TransformFloat3(const char* label, float *v, float resetValue = 0.0f, float columnWidth = 100.0f);
}